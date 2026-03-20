import finnhub
from datetime import date, timedelta
import datetime

# Your API key here
API_KEY = 'd4flpchr01qsjdiqgds0d4flpchr01qsjdiqgdsg'

# Initialize client
client = finnhub.Client(api_key=API_KEY)

# Dates
current_date = date.today()
date_minus_week = current_date - timedelta(weeks=1)

def getNews(ticker):
    dat = client.company_news(
        symbol=ticker,
        _from=date_minus_week.isoformat(),  # convert date to 'YYYY-MM-DD'
        to=current_date.isoformat()
    )
    return dat

def getMarket():
    res = client.stock_candles(
        symbol = '^GSPC',
        resolution = 'D',
        _from = date_minus_week.isoformat(),
        to = current_date.isoformat()
    )
    return res