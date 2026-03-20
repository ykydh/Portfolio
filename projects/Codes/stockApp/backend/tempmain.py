import threading
import time
import threadFunc as th
import db
import sys
#debugg segfault
import torch
torch.set_num_threads(1)
torch.set_num_interop_threads(1)



def stock_thread(shutdown_event):
    while not shutdown_event.is_set():
        th.backfillStockHistory()
        #print("stock : pass")
        # sleep but exit early if shutdown_event is set
        if shutdown_event.wait(3*60*60):
            return


def news_thread(shutdown_event):
    while not shutdown_event.is_set():
        th.updatingNews()
        #print("News update: pass")
        # sleep but exit early if shutdown_event is set
        if shutdown_event.wait(2.5*60*60):
            return

          
def prediction_thread(shutdown_event):
    while th.sync_prevention == True:
        sys.wait(30)

    while not shutdown_event.is_set():
        th.prediction()
        #print("prediction: pass")
        if shutdown_event.wait(60):
            return


def input_thread(shutdown_event):
    while not shutdown_event.is_set():
        th.userInput()
        print("Quit: Y/N")
        judge = input()
        if judge.upper() == 'Y':
            shutdown_event.set()
            return
        #print("Input: pass")


if __name__ == "__main__":
    db.dbInitialize()

    shutdown_event = threading.Event()

    t1 = threading.Thread(target=input_thread, args=(shutdown_event,), daemon=True)
    t2 = threading.Thread(target=stock_thread, args=(shutdown_event,), daemon=True)
    t3 = threading.Thread(target=news_thread, args=(shutdown_event,), daemon=True)
    t4 = threading.Thread(target=prediction_thread,  args=(shutdown_event,), daemon=True)

    t1.start()
    t2.start()
    t3.start()
    t4.start()

    # Wait until shutdown event is set
    shutdown_event.wait()

    print("Shutting down all threads...")
    print("Goodbye!")
    sys.exit(0)










