import db
import sqlite3
import news_API as nAPI
import stock_API as sAPI
import prediction as pred
from datetime import datetime, timedelta
import numpy as np
import threading

# -------------------------------
# Synchronization flag
# -------------------------------
backfill_done = threading.Event()  # signal that backfill is complete

# -------------------------------
# DB WRITER (fixed)
# -------------------------------
def db_writer():
    conn = sqlite3.connect(db.DB_PATH, check_same_thread=False)
    cur = conn.cursor()
    print("DB Writer started")

    while True:
        job = db.db_queue.get()
        try:
            if job is None:
                conn.commit()
                conn.close()
                break

            job_type = job[0]

            if job_type == "update_prediction":
                _, stock_id, ts, pred_price, conf = job
                # FIXED: use INSERT OR REPLACE to handle duplicates
                cur.execute("""
                    INSERT OR REPLACE INTO prediction (stock_id, timestamp, prediction, confidence)
                    VALUES (?, ?, ?, ?)
                """, (stock_id, ts, pred_price, conf))

            elif job_type == "update_news":
                _, stock_id, headline, summary, source, score, confidence, published_at = job
                # Optional: only insert unique news per stock and timestamp
                cur.execute("""
                    INSERT OR IGNORE INTO news (
                        stock_id, headline, summary, source,
                        score, confidence, published_at
                    )
                    VALUES (?, ?, ?, ?, ?, ?, ?)
                """, (
                    stock_id,
                    headline,
                    summary,
                    source,
                    score,
                    confidence,
                    published_at.strftime("%Y-%m-%d %H:%M:%S")
                ))

            elif job_type == "add_history":
                _, stock_id, timestamp, price, volume = job
                cur.execute("""
                    INSERT INTO stockHistory (stock_id, timestamp, price, volume)
                    VALUES (?, ?, ?, ?)
                    ON CONFLICT(stock_id, timestamp) DO UPDATE SET
                    price=excluded.price,
                    volume=excluded.volume
                """, (stock_id, timestamp, price, volume))

            elif job_type == "add_market":
                _, close, open_price, high, low, timestamp, volume = job
                cur.execute("""
                    INSERT OR IGNORE INTO market (
                        close_price, open_price, high_price,
                        low_price, timestamp, volume
                    )
                    VALUES (?, ?, ?, ?, ?, ?)
                """, (close, open_price, high, low, timestamp, volume))

            elif job_type == "purchase_stock":
                _, ticker, exchange, price, volume = job

                # Check if stock already exists
                cur.execute("""
                    SELECT stock_id,purchased_price,volume
                    FROM stock
                    WHERE ticker = ? AND exchange = ?
                """, (ticker, exchange))

                result = cur.fetchone()

                if result:
                    stock_id, price, current_volume = result

                    # update volume
                    cur.execute("""
                        UPDATE stock
                        SET 
                            purchased_price = ((purchased_price * ?) + (? * ?)) / (? + ?),
                            volume = volume + ?
                        WHERE stock_id = ?
                    """, (current_volume, price, volume, current_volume, volume, volume, stock_id))

                else:
                    # insert new stock
                    cur.execute("""
                        INSERT INTO stock (ticker, exchange, purchased_price, volume)
                        VALUES (?, ?, ?, ?)
                    """, (ticker, exchange, price, volume))

                    stock_id = cur.lastrowid

                # insert snapshot into stockNow

            elif job_type == "current_price_updation":
                _, stock_id, price, volume = job

                cur.execute("""
                    REPLACE INTO stockNow (stock_id, timestamp, price, volume)
                    VALUES (?, datetime('now'), ?, ?)
                """, (stock_id, price, volume))

            elif job_type == "current_prediction_updation":
                _, stock_id, ts, pred_price, conf = job

                cur.execute("""
                    INSERT INTO predictionNow (stock_id, timestamp, prediction, confidence)
                    VALUES (?, ?, ?, ?)
                    ON CONFLICT(stock_id)
                    DO UPDATE SET
                        timestamp = excluded.timestamp,
                        prediction = excluded.prediction,
                        confidence = excluded.confidence
                """, (stock_id, ts, pred_price, conf))

            conn.commit()

        except Exception as e:
            print("!!!!!DB WRITER ERROR:", e)

        finally:
            db.db_queue.task_done()
# -------------------------------
# STOCK FUNCTIONS
# -------------------------------
def backfillStockHistory():
    allStocks = db.getAllStocks()
    now = datetime.now()

    with db.get_conn() as conn:
        cursor = conn.cursor()
        for stock in allStocks:
            ticker = stock[1]
            stock_id = db.getStockId(stock[1], stock[2])

            cursor.execute("""
                SELECT timestamp
                FROM stockHistory
                WHERE stock_id = ?
                ORDER BY timestamp DESC
                LIMIT 1
            """, (stock_id,))
            latest = cursor.fetchone()

            if latest is None:
                begin_date = now - timedelta(days=365*2)
            else:
                begin_date = datetime.strptime(latest[0], "%Y-%m-%d %H:%M:%S")

            try:
                data = sAPI.getStockData(ticker, begin_date)
            except Exception as e:
                print(f"Failed to get stock data for {ticker}: {e}")
                continue  # skip this stock but continue the loop

            if not data:
                print(f"No historical data returned for {ticker}")
                continue

            for row in data:
                db.db_queue.put((
                    "add_history",
                    stock_id,
                    row['timestamp'].strftime("%Y-%m-%d %H:%M:%S"),
                    float(row['adj_close']),
                    int(row['volume'])
                ))

        conn.commit()  # commit after all stocks

    backfill_done.set()  # signal backfill is complete



def stockNow():
    all_stocks = db.getAllStocks()

    for stock in all_stocks:
        stock_id = stock[0]
        ticker = stock[1]

        data = sAPI.fetchStockNow(ticker)

        if not data:
            continue

        price = data["price"]
        volume = data["volume"]

        db.db_queue.put((
            "current_price_updation",
            stock_id,
            price,
            volume
        ))
# -------------------------------
# NEWS FUNCTIONS
# -------------------------------
def updatingNews():
    allStocks = db.getAllStocks()
    print(allStocks)
    db.deleteAllNews()  

    for stock in allStocks:
        stock_id = db.getStockId(stock[1], stock[2])
        dat = nAPI.getNews(stock[1])

        for news in dat:
            headline = news['headline']
            summary = news['summary']
            source = news['source']
            ts = news['datetime']

            parser = headline + " " + summary
            confidence, score = pred.sentiment_analyze(parser)
            published_at = datetime.fromtimestamp(ts)

            db.db_queue.put((
                "update_news",
                stock_id,
                headline,
                summary,
                source,
                score,
                confidence,
                published_at
            ))

# -------------------------------
# PREDICTION FUNCTIONS
# -------------------------------
def prediction():
    backfill_done.wait()  # minimal change: wait until backfill is done
    stocks = db.getAllStocks()
    print(stocks)
    if not stocks:
        return

    today = datetime.now()
    sAPI.fetchSP500()

    for stock in stocks:
        stock_id = stock[0]

        market_history = db.getMarket()
        if len(market_history) < 6:
            continue
        market_sorted = sorted(market_history, key=lambda x: x[0])
        market_prices = [float(h[1]) for h in market_sorted[-6:]]

        history = db.getHistory(stock_id)
        if len(history) < 6:
            continue
        history_sorted = sorted(history, key=lambda x: x[0])
        prices = [float(h[1]) for h in history_sorted[-6:]]

        sentiments = []
        for i in range(5):
            day = today - timedelta(days=4 - i)
            s = db.daily_sentiment(stock_id, day)
            sentiments.append(s if s is not None else 0.0)

        X, y = pred.buildFeatures(stock_id)
        if X is None or y is None:
            continue

        model = pred.trainXgboostModel(X, y)
        prices_arr = np.asarray(prices, dtype=float)
        sentiments_arr = np.asarray(sentiments, dtype=float)
        market_arr = np.asarray(market_prices, dtype=float)

        try:
            mean_pred, confidence = pred.predictNextDayWithConfidence(
                [model], prices_arr, market_arr, sentiments_arr, lookback=5
            )
        except Exception:
            continue

        last_price = prices_arr[-1]
        predicted_price = last_price * (1 + mean_pred)

        db.db_queue.put((
            "update_prediction",
            stock_id,
            today,
            predicted_price,
            confidence
        ))

        db.db_queue.put((
            "current_prediction_updation",
            stock_id,
            today,
            predicted_price,
            confidence
        ))

        print(f"Predicted {stock_id}: {predicted_price:.2f}")

# -------------------------------
# THREAD FUNCTIONS
# -------------------------------
def stock_thread(shutdown_event):
    backfillStockHistory()
    while not shutdown_event.is_set():
        if shutdown_event.wait(12*60*60):
            return

def news_thread(shutdown_event):
    while not shutdown_event.is_set():
        updatingNews()
        if shutdown_event.wait(2*60*60):
            return

def prediction_thread(shutdown_event):
    backfill_done.wait()  # minimal change
    while not shutdown_event.is_set():
        prediction()
        if shutdown_event.wait(10*60):
            return

def updateStockNow(shutdown_event):
    while not shutdown_event.is_set():
        stockNow()
        if shutdown_event.wait(5*60):
            return

