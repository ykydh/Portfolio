import sqlite3
from datetime import datetime
import math
import numpy as np
import struct
import os
from queue import Queue

db_queue = Queue()

# --- DATABASE CONFIG ---


DB_PATH = "/Users/yutarokiyota/Desktop/stockApp/backend/stocks.db"

def get_conn():
    base_dir = os.path.dirname(os.path.abspath(DB_PATH))
    if base_dir and not os.path.exists(base_dir):
        os.makedirs(base_dir, exist_ok=True)
    return sqlite3.connect(DB_PATH, check_same_thread=False, timeout=30)

# --- SAFE EXECUTE ---
def safe_execute(query, params=(), fetch=False, commit=False):
    with get_conn() as conn:
        cur = conn.cursor()
        cur.execute(query, params)
        if commit:
            conn.commit()
        if fetch:
            return cur.fetchall()
        return None

# --- DATABASE INITIALIZATION ---
def dbInitialize():
    with get_conn() as conn:
        cursor = conn.cursor()
        cursor.executescript("""
        CREATE TABLE IF NOT EXISTS stock (
            stock_id INTEGER PRIMARY KEY AUTOINCREMENT,
            ticker VARCHAR(5),
            exchange VARCHAR(10),
            purchased_price REAL,
            volume INTEGER,
            UNIQUE(ticker, exchange)
        );

        CREATE TABLE IF NOT EXISTS stockHistory (
            history_id INTEGER PRIMARY KEY AUTOINCREMENT,
            stock_id INTEGER,
            timestamp DATETIME,
            price REAL,
            volume INTEGER,
            FOREIGN KEY(stock_id) REFERENCES stock(stock_id) ON DELETE CASCADE,
            UNIQUE(stock_id, timestamp)
        );
                             
        CREATE TABLE IF NOT EXISTS stockNow (
            stock_id INTEGER UNIQUE,
            timestamp DATETIME,
            price REAL,
            volume INTEGER,
            FOREIGN KEY(stock_id) REFERENCES stock(stock_id) ON DELETE CASCADE
        );

        CREATE TABLE IF NOT EXISTS predictionNow (
            stock_id INTEGER UNIQUE,
            timestamp DATETIME,
            prediction REAL,
            confidence REAL,
            FOREIGN KEY(stock_id) REFERENCES stock(stock_id) ON DELETE CASCADE
        );

        CREATE TABLE IF NOT EXISTS news (
            news_id INTEGER PRIMARY KEY AUTOINCREMENT,
            stock_id INTEGER,
            headline TEXT,
            summary TEXT,
            source VARCHAR(50),
            score INTEGER,
            confidence INTEGER,
            published_at DATETIME,
            FOREIGN KEY(stock_id) REFERENCES stock(stock_id) ON DELETE CASCADE
        );

    
        CREATE TABLE IF NOT EXISTS prediction (
            prediction_id INTEGER PRIMARY KEY AUTOINCREMENT,
            stock_id INTEGER,
            timestamp DATETIME,
            prediction REAL,
            confidence REAL,
            FOREIGN KEY(stock_id) REFERENCES stock(stock_id) ON DELETE CASCADE,
            UNIQUE(stock_id, timestamp)
        );

        CREATE TABLE IF NOT EXISTS jobs (
            job_id INTEGER PRIMARY KEY AUTOINCREMENT,
            stock_id INTEGER,
            job_type VARCHAR(20),
            status VARCHAR(20),
            created_at DATETIME,
            updated_at DATETIME,
            FOREIGN KEY(stock_id) REFERENCES stock(stock_id) ON DELETE CASCADE
        );

        CREATE TABLE IF NOT EXISTS market (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            close_price REAL NOT NULL,
            open_price REAL,
            high_price REAL,
            low_price REAL,
            timestamp DATETIME,
            volume INTEGER,
            UNIQUE(timestamp)
        );
        """)
        conn.commit()

# --- STOCK OPERATIONS ---
'''
def purchasedStock(ticker, exchange, price, volume):
    safe_execute("""
        INSERT INTO stock(ticker, exchange, purchased_price, volume)
        VALUES (?, ?, ?, ?)
    """, (ticker, exchange, price, volume), commit=True)
'''
def sellStock(tic, exc, price, volume_sell):
    volume_sell = float(volume_sell)
    price = float(price)
    with get_conn() as conn:
        cur = conn.cursor()
        cur.execute("SELECT purchased_price, volume FROM stock WHERE ticker=? AND exchange=?", (tic, exc))
        result = cur.fetchone()
        if not result:
            return None
        purchased_price, current_volume = map(float, result)
        if volume_sell > current_volume:
            print(f"Cannot sell more than you own: {tic} ({current_volume})")
            return None
        gain = (price - purchased_price) * volume_sell
        volume_left = current_volume - volume_sell
        if volume_left == 0:
            cur.execute("DELETE FROM stock WHERE ticker=? AND exchange=?", (tic, exc))
        else:
            cur.execute("UPDATE stock SET volume=? WHERE ticker=? AND exchange=?", (volume_left, tic, exc))
        conn.commit()
        return gain

# --- MARKET OPERATIONS ---
'''
def addMarket(close, open, high, low, timestamp, volume):
    safe_execute("""
        INSERT OR IGNORE INTO market(close_price, open_price, high_price, low_price, timestamp, volume)
        VALUES (?, ?, ?, ?, ?, ?)
    """, (close, open, high, low, timestamp, volume), commit=True)
'''
def marketReturn():
    rows = safe_execute("SELECT close_price FROM market ORDER BY timestamp ASC", fetch=True)
    if not rows or len(rows) < 2:
        return None
    closes = np.array([r[0] for r in rows], dtype=float)
    returns = np.diff(closes) / closes[:-1]
    return returns

def getMarket():
    return safe_execute("SELECT timestamp, close_price, volume FROM market ORDER BY timestamp ASC", fetch=True) or []

# --- STOCK HISTORY ---
'''
def addHistory(stock_id, timestamp, price, volume):
    safe_execute("""
        INSERT INTO stockHistory(stock_id, timestamp, price, volume)
        VALUES (?, ?, ?, ?)
    """, (stock_id, timestamp, price, volume), commit=True)
'''
def stockReturns(Sid):
    rows = safe_execute("SELECT price FROM stockHistory WHERE stock_id=? ORDER BY timestamp ASC", (Sid,), fetch=True)
    if not rows or len(rows) < 2:
        return None
    closes = np.array([r[0] for r in rows], dtype=float)
    returns = np.diff(closes) / closes[:-1]
    return returns

# --- NEWS ---
'''
def updateNews(stock_id, headline, summary, source, score, confidence, datatime):
    safe_execute("""
        INSERT INTO news(stock_id, headline, summary, source, score, confidence, published_at)
        VALUES (?, ?, ?, ?, ?, ?, ?)
    """, (stock_id, headline, summary, source, score, confidence, datatime), commit=True)
'''
def getNews(stock_id):
    return safe_execute("""
        SELECT headline, summary, source, score, confidence, published_at
        FROM news
        WHERE stock_id=?
        ORDER BY published_at DESC
    """, (stock_id,), fetch=True) or []

def confidenceSummation(Sid):
    rows = safe_execute("SELECT score, confidence, published_at FROM news WHERE stock_id=?", (Sid,), fetch=True) or []
    now = datetime.now()
    decay_rate = 0.2
    scores = []
    for score, confidence, published_at in rows:
        if isinstance(published_at, str):
            published_at = datetime.fromisoformat(published_at)
        age_days = (now - published_at).days
        weight = math.exp(-decay_rate * age_days)
        scores.append(score * confidence * weight)
    return sum(scores)

# --- PREDICTION ---
'''
def updatePrediction(stock_id, timestamp, prediction, confidence):
    safe_execute("""
        INSERT INTO prediction(stock_id, timestamp, prediction, confidence)
        VALUES (?, ?, ?, ?)
    """, (stock_id, timestamp, prediction, confidence), commit=True)
'''
def getPrediction(stock_id):
    row = safe_execute("""
        SELECT timestamp, prediction, confidence
        FROM prediction
        WHERE stock_id=?
        ORDER BY timestamp DESC
        LIMIT 1
    """, (stock_id,), fetch=True)
    if not row:
        return None
    timestamp, prediction, confidence = row[0]
    if isinstance(confidence, (bytes, bytearray)):
        confidence = struct.unpack("f", confidence)[0]
    return {"timestamp": timestamp, "prediction": float(prediction), "confidence": float(confidence)}

def getPredictionsHist(stock_id):
    return safe_execute("""
        SELECT timestamp, prediction, confidence
        FROM prediction
        WHERE stock_id=?
        ORDER BY timestamp DESC
    """, (stock_id,), fetch=True) or []

def getPredictionNow():
    return safe_execute("SELECT * FROM predictionNow", fetch=True) or []


def getSinglePrediction(stock_id):
    return safe_execute(
        "SELECT * FROM predictionNow WHERE stock_id=?",
        (stock_id,), 
        fetch=True
    )

# --- STOCK GETTERS ---
def getStockId(ticker, exchange):
    row = safe_execute("SELECT stock_id FROM stock WHERE ticker=? AND exchange=?", (ticker, exchange), fetch=True)
    return row[0][0] if row else None

def getSingleStock(ticker):
    return safe_execute(
        "SELECT * FROM stock WHERE ticker=?",
        (ticker,), 
        fetch=True
    )

def getAllStocks():
    return safe_execute("SELECT * FROM stock", fetch=True) or []

def getAllStockNow():
    return safe_execute("SELECT * FROM stockNow", fetch=True) or []

def getHistory(stock_id):
    return safe_execute("""
        SELECT timestamp, price, volume
        FROM stockHistory
        WHERE stock_id=?
        ORDER BY timestamp DESC
    """, (stock_id,), fetch=True) or []

def deleteAllNews():
    safe_execute("DELETE FROM news", commit=True)

# --- DAILY SENTIMENT ---
def daily_sentiment(Sid, date):
    rows = safe_execute("SELECT score, confidence, published_at FROM news WHERE stock_id=?", (Sid,), fetch=True) or []
    sentiment_sum = 0
    decay_rate = 0.2
    now = date
    for score, confidence, published_at in rows:
        if isinstance(published_at, str):
            try:
                published_at_dt = datetime.strptime(published_at, "%Y-%m-%d %H:%M:%S")
            except ValueError:
                published_at_dt = datetime.strptime(published_at, "%Y-%m-%d")
        else:
            published_at_dt = published_at
        if (now - published_at_dt).days < 7:
            weight = math.exp(-decay_rate * (now - published_at_dt).days)
            sentiment_sum += score * confidence * weight
    return sentiment_sum