import yfinance as yf
from datetime import datetime, timedelta, time
import db as db

def getStockData(ticker, start_date):
    end_date = datetime.now().strftime("%Y-%m-%d")  # yfinance expects string dates
    start_date_str = start_date.strftime("%Y-%m-%d")

    print(f"Fetching {ticker} from {start_date_str} to {end_date}")

    dat = yf.download(
        ticker,
        start=start_date_str,
        end=end_date,
        interval='1d',
        auto_adjust=True,
        progress=False
    )

    result = []
    for idx, row in dat.iterrows():
        # Ensure types are correct
        timestamp = idx.to_pydatetime().replace(hour=0, minute=0, second=0, microsecond=0)
        adj_close = float(row['Close'].iloc[0])
        volume = int(row['Volume'].iloc[0])

        result.append({
            'timestamp': timestamp,
            'adj_close': adj_close,
            'volume': volume
        })

    return result


def fetch_latest_stock(ticker):
    yesterday = datetime.today() - timedelta(days=1)
    today = datetime.today()
    
    dat = yf.download(
        ticker,
        start=yesterday.strftime("%Y-%m-%d"),
        end=today.strftime("%Y-%m-%d"),
        interval="1d",
        auto_adjust=True,
        progress=False
    )
    
    if dat.empty:
        return None
    
    latest_row = dat.iloc[-1]
    timestamp = latest_row.name.to_pydatetime()  # convert pandas Timestamp to Python datetime
    adj_close = latest_row['Close']
    volume = latest_row['Volume']
    
    return {'timestamp': timestamp, 'adj_close': adj_close, 'volume': volume}



def fetchStockNow(ticker):
    try:
        t = yf.Ticker(ticker)
        info = t.info

        price = info.get("regularMarketPrice") or info.get("currentPrice")
        volume = info.get("volume")

        if price is None:
            return None

        return {
            "timestamp": datetime.now(),
            "price": round(float(price), 2),
            "volume": int(volume) if volume else 0
        }

    except Exception as e:
        print(f"Failed to fetch {ticker}: {e}")
        return None

def fetchSP500():
    sp500 = yf.Ticker("^GSPC")
    hist = sp500.history(period="2y", interval="1d").reset_index()

    for _, row in hist.iterrows():
        #convert to py date time
        timestamp = row['Date'].to_pydatetime()


        open_price = float(row['Open'])
        high_price = float(row['High'])
        low_price = float(row['Low'])
        close_price = float(row['Close'])
        volume = int(row['Volume'])

        db.db_queue.put((
            "add_market",
            close_price,
            open_price,
            high_price,
            low_price,
            timestamp,
            volume
        ))

