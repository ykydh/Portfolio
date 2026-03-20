import numpy as np
from datetime import datetime, timedelta
import db
import xgboost as xgb
import os
os.environ["OMP_NUM_THREADS"] = "1"
os.environ["MKL_NUM_THREADS"] = "1"

import torch
import torch.nn.functional as F
from transformers import AutoTokenizer, AutoModelForSequenceClassification
import threading

device = torch.device("mps" if torch.backends.mps.is_available() else "cpu")

tokenizer = AutoTokenizer.from_pretrained("yiyanghkust/finbert-tone")
model = AutoModelForSequenceClassification.from_pretrained("yiyanghkust/finbert-tone")
model.to(device)
model.eval()

sentiment_lock = threading.Lock()

def sentiment_analyze(text: str):
    if not text.strip():
        return 0.0, 0.0

    with sentiment_lock:
        inputs = tokenizer(text, return_tensors="pt", truncation=True, max_length=512)
        inputs = {k: v.to(device) for k, v in inputs.items()}
        with torch.no_grad():
            logits = model(**inputs).logits.squeeze(0)
        probs = F.softmax(logits, dim=0)
        pos, neu, neg = probs[0].item(), probs[1].item(), probs[2].item()
        score = pos - neg
        confidence = max(pos, neu, neg)
        return score, confidence
# ----------------------------
# Build training features for XGBoost
# ----------------------------
def buildFeatures(Sid, lookback=5, clip_value=1.0):
    stock_returns = db.stockReturns(Sid)
    market_returns = db.marketReturn()

    if stock_returns is None or market_returns is None:
        print("Missing stock or market returns")
        return None, None

    stock_returns = np.asarray(stock_returns, dtype=float)
    market_returns = np.asarray(market_returns, dtype=float)

    # Align lengths
    n_days = min(len(stock_returns), len(market_returns))
    stock_returns = stock_returns[-n_days:]
    market_returns = market_returns[-n_days:]

    # Remove NaN / inf
    valid_mask = np.isfinite(stock_returns) & np.isfinite(market_returns)
    stock_returns = stock_returns[valid_mask]
    market_returns = market_returns[valid_mask]

    # Clip extreme values
    stock_returns = np.clip(stock_returns, -clip_value, clip_value)
    market_returns = np.clip(market_returns, -clip_value, clip_value)

    n_days = len(stock_returns)
    if n_days <= lookback + 1:
        print("Not enough usable data after cleaning")
        return None, None

    X_list = []
    y_list = []

    for t in range(lookback, n_days - 1):
        features = []
        features.extend(stock_returns[t - lookback:t])
        features.extend(market_returns[t - lookback:t])

        # Sentiment
        date_today = datetime.now() - timedelta(days=(n_days - t - 1))
        sentiment = float(db.daily_sentiment(Sid, date_today) or 0.0)
        sentiment = np.clip(sentiment, -clip_value, clip_value)
        features.append(sentiment)

        # Clip features again
        features = [np.clip(f, -clip_value, clip_value) for f in features]

        X_list.append(features)
        y_list.append(stock_returns[t])

    if len(X_list) == 0:
        print("No valid training samples")
        return None, None

    X = np.asarray(X_list, dtype=float)
    y = np.asarray(y_list, dtype=float)

    # Safety: replace any remaining inf or NaN
    X = np.nan_to_num(X, nan=0.0, posinf=clip_value, neginf=-clip_value)
    y = np.nan_to_num(y, nan=0.0, posinf=clip_value, neginf=-clip_value)

    if X.ndim != 2 or X.shape[0] < 10:
        print("Insufficient training samples")
        return None, None
    if np.std(y) == 0:
        print("Target has zero variance")
        return None, None

    return X, y


# ----------------------------
# Train XGBoost model
# ----------------------------
def trainXgboostModel(X, y):
    model = xgb.XGBRegressor(
        n_estimators=200,
        max_depth=5,
        learning_rate=0.05,
        subsample=0.8,
        colsample_bytree=0.8,
        objective='reg:squarederror'
    )
    model.fit(X, y)
    return model


# ----------------------------
# Build today's features
# ----------------------------
def build_today_features(prices, market_prices, sentiments, lookback=5, clip_value=1.0):
    prices = np.asarray(prices, dtype=float)
    market_prices = np.asarray(market_prices, dtype=float)
    sentiments = [float(s) if s is not None else 0.0 for s in sentiments]

    if len(prices) < lookback + 1 or len(market_prices) < lookback + 1:
        raise ValueError("Not enough price data for prediction")

    stock_returns = (prices[1:] - prices[:-1]) / prices[:-1]
    stock_returns = np.clip(stock_returns[-lookback:], -clip_value, clip_value)
    stock_returns = np.nan_to_num(stock_returns, nan=0.0)

    market_returns = (market_prices[1:] - market_prices[:-1]) / market_prices[:-1]
    market_returns = np.clip(market_returns[-lookback:], -clip_value, clip_value)
    market_returns = np.nan_to_num(market_returns, nan=0.0)

    sentiment_today = sentiments[-1] if sentiments else 0.0
    sentiment_today = np.clip(sentiment_today, -clip_value, clip_value)

    features = np.concatenate([stock_returns, market_returns, [sentiment_today]]).reshape(1, -1)
    features = np.nan_to_num(features, nan=0.0, posinf=clip_value, neginf=-clip_value)
    return features


# ----------------------------
# Predict next day with confidence
# ----------------------------
def predictNextDayWithConfidence(models, prices, market_prices, sentiments, lookback=5, clip_value=1.0):
    X_today = build_today_features(prices, market_prices, sentiments, lookback, clip_value)
    preds = np.array([model.predict(X_today)[0] for model in models])

    mean_pred = preds.mean()
    uncertainty = preds.std()
    confidence = 1 / (1 + uncertainty)

    return mean_pred, confidence