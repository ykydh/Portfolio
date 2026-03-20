import os
import db

print("Absolute DB path:", os.path.abspath(db.DB_PATH))
print("DB exists:", os.path.exists(os.path.abspath(db.DB_PATH)))

from fastapi import FastAPI, Query
from datetime import datetime, timedelta
import time
import threading
import struct


import db as db
import threadFunc as helper
from pydantic import BaseModel
from fastapi.middleware.cors import CORSMiddleware
from fastapi.responses import FileResponse


class SellStockRequest(BaseModel):
    price: float
    volume_sell: float

# -------------------------------
# Lifespan for background threads
# -------------------------------
from contextlib import asynccontextmanager

@asynccontextmanager
async def lifespan(app: FastAPI):
    # Initialize DB
    db.dbInitialize()

    # Shutdown event for threads
    shutdown_event = threading.Event()

    # Start threads
    threads = [
        threading.Thread(target=helper.stock_thread, args=(shutdown_event,), daemon=True),
        threading.Thread(target=helper.news_thread, args=(shutdown_event,), daemon=True),
        threading.Thread(target=helper.prediction_thread, args=(shutdown_event,), daemon=True),
        threading.Thread(target=helper.db_writer, daemon=True),
        threading.Thread(target=helper.updateStockNow, args=(shutdown_event,), daemon=True)
    ]

    for t in threads:
        t.start()

    try:
        yield
    finally:
        shutdown_event.set()
        for t in threads:
            t.join(timeout=2)

app = FastAPI(lifespan=lifespan)

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # allow everything for now
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)
'''
app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:3000"],  # your React dev URL
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)
'''
# -------------------------------
# Health Check
# -------------------------------
@app.get("/")
def health():
    return {"status": "ok", "message": "Stock API running"}

# -------------------------------
# Prediction
# -------------------------------
@app.put("/prediction/update")
def predict():
    try:
        helper.prediction()  # queues DB writes
        return {"status": "prediction queued"}
    except Exception as e:
        return {"error_prediction": str(e)}

@app.get("/prediction/latest/{exchange}/{ticker}")
def getPredictionEndpoint(exchange: str, ticker: str):
    stock_id = db.getStockId(ticker, exchange)

    if stock_id is None:
        return {"error": "Stock not found"}

    result = db.getPrediction(stock_id)

    if result is None:
        return {"error": "No prediction found"}

    return result

# -------------------------------
# Stock endpoints
# -------------------------------
@app.post("/stock/add/{exchange}/{ticker}")
def addStock(exchange: str, ticker: str, price: float = Query(...), volume: int = Query(...)):
    try:
        db.db_queue.put((
            "purchase_stock",
            ticker, 
            exchange, 
            price, 
            volume
        ))
        return {"status": "stock purchase queued"}
    except Exception as e:
        return {"error_stock_purchase": str(e)}

@app.delete("/stock/sell/{exchange}/{ticker}")
def sellStock(exchange: str, ticker: str, req: SellStockRequest):
    try:
        gain = db.sellStock(ticker, exchange, req.price, req.volume_sell)
        return {"gain": gain}
    except Exception as e:
        return {"error_stock_selling": str(e)}

@app.put("/stock/update")
def updateStocks():
    try:
        helper.backfillStockHistory()
        return {"status": "stock update queued"}
    except Exception as e:
        return {"error_stock_update": str(e)}

@app.get("/stock/info")
def getAllStocks():
    try:
        stocks = db.getAllStocks()
        return stocks
    except Exception as e:
        return {"error_stock_info": str(e)}

@app.get("/stock/single")
def getAStock(ticker: str):
    try:
        stock = db.getSingleStock(ticker)
        return stock
    except Exception as e:
        return {"error_stock_info": str(e)}

  
@app.get("/stock/topthree")
def getTopThree():
    try:
        stocks = db.getAllStocks()
        stocksNow = db.getAllStockNow()

        now_lookup = {j[0]: j for j in stocksNow}

        results = []

        for s in stocks:
            stock_id = s[0]
            ticker = s[1]
            purchase_price = s[3]

            if stock_id in now_lookup:
                current_price = now_lookup[stock_id][2]

                diff = current_price - purchase_price
                percent_change = round((diff / purchase_price) * 100, 2)
                results.append({
                    "ticker": ticker,
                    "diff": round(abs(diff), 2),
                    "up": diff > 0,
                    "percentage" :percent_change
                })

        results.sort(key=lambda x: x["diff"], reverse=True)

        return results[:3]

    except Exception as e:
        return {"error_stock_info": str(e)}
    
@app.get("/stock/current")
def getCurrentStocks():
    """
    Return all stocks with their latest prices from stockNow table.
    """
    try:
        stocks_now = db.getAllStockNow()  # calls your existing function
        # Convert to list of dicts for JSON
        result = []
        for s in stocks_now:
            stock_id, timestamp, price, volume = s
            result.append({
                "stock_id": stock_id,
                "timestamp": timestamp,
                "price": price,
                "volume": volume
            })
        return result
    except Exception as e:
        return {"error": str(e)}
    


def to_float(val):
    """
    Convert database value to float safely.
    Handles bytes, str, int, float.
    """
    if val is None:
        return 0.0

    if isinstance(val, bytes):
        try:
            return struct.unpack('f', val)[0]
        except:
            return 0.0

    try:
        return float(val)
    except:
        return 0.0


@app.get("/stock/topthree/current")
def getTopThreeCurrentAndForecast():
    try:
        # Step 1: Get top 3 movement stocks
        top3 = getTopThree() or []

        # Step 2: Map ticker -> stock_id
        all_stocks = db.getAllStocks() or []
        ticker_to_id = {s[1]: s[0] for s in all_stocks}

        # Step 3: Latest stock prices
        stocks_now = db.getAllStockNow() or []
        now_lookup = {s[0]: s for s in stocks_now}

        # Step 4: Latest predictions
        predictions_now = db.getPredictionNow() or []
        pred_lookup = {p[0]: p for p in predictions_now}

        result = []

        for stock in top3:
            ticker = stock.get("ticker")
            stock_id = ticker_to_id.get(ticker)

            if not stock_id or stock_id not in now_lookup:
                continue

            current = now_lookup[stock_id]
            pred = pred_lookup.get(stock_id)

            price = to_float(current[2])
            percentage = to_float(stock.get("percentage", 0))

            predicted_price = "-"
            confidence = "-"

            if pred:
                predicted_price = round(to_float(pred[2]), 2)
                confidence = round(to_float(pred[3]), 2)

            item = {
                "ticker": ticker,
                "price": round(price, 2),
                "volume": current[3],
                "up": stock.get("up", True),
                "percentage": round(percentage, 2),
                "predicted_price": predicted_price,
                "confidence": confidence
            }

            result.append(item)

        return result

    except Exception as e:
        print("Error in /stock/topthree/current:", e)
        return []

@app.get("/prediction/current/single")
def getAStock(ticker: str):
    try:
        prediction = db.getSinglePrediction(ticker)
        return prediction
    except Exception as e:
        return {"error_current_prediction_info": str(e)}
    
#stock has to be now stoc 
@app.get("/stock/single/prediction")
def getAStockWithPrediction(ticker: str):
    try:
        # Step 1: Get stock info
        stock_list = db.getSingleStock(ticker)  # returns list of tuples
        if not stock_list:
            return {"error": "Stock not found"}

        stock = stock_list[0]  # (stock_id, ticker, exchange, purchased_price, volume)
        stock_id = stock[0]

        # Step 2: Get latest price for this stock
        current_list = db.getAllStockNow() or []
        current_lookup = {s[0]: s for s in current_list}  # stock_id -> (stock_id, timestamp, price, volume)

        if stock_id not in current_lookup:
            return {"error": "Current price not found"}

        current_price = round(to_float(current_lookup[stock_id][2]), 2)
        volume = current_lookup[stock_id][3]

        # Step 3: Calculate up/down and percentage based on purchased price
        purchased_price = to_float(stock[3])
        up = current_price >= purchased_price
        percentage = round(((current_price - purchased_price) / purchased_price) * 100, 2)

        # Step 4: Get latest prediction
        prediction_list = db.getSinglePrediction(stock_id) or []
        if prediction_list:
            pred = prediction_list[0]  # (stock_id, timestamp, prediction, confidence)
            predicted_price = round(to_float(pred[2]), 2)
            confidence = round(to_float(pred[3]), 2)
        else:
            predicted_price = "-"
            confidence = "-"

        # Step 5: Combine result
        result = {
            "stock_id": stock_id,
            "ticker": stock[1],
            "exchange": stock[2],
            "current_price": current_price,
            "volume": volume,
            "up": up,
            "percentage": percentage,
            "predicted_price": predicted_price,
            "confidence": confidence
        }

        return result

    except Exception as e:
        print("ERROR:", e)
        return {"error": str(e)}