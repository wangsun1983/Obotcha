import socket
import threading
import time
import http
import requests

class ConnectThread(threading.Thread):
    def __init__(self,threadID,loopcount,sendcount,ip,port):
        threading.Thread.__init__(self)
        self.id = threadID
        self.mytid = threading
        self.loopcount = loopcount
        self.address = (ip,port)
        self.sendcount = sendcount

    def run(self):
        count = self.loopcount
        while count > 0:
            content = "thread " + str(self.id) + " : " + str(count) 
            response = requests.get('http://192.168.1.3:1122', 
							 data = content)
            print("get response")
            print(response.text)
            time.sleep(0.01)
            count = count - 1

#start test
threadcount = 0
threads = []
while threadcount < 1:
    thread = ConnectThread(threadcount,1024,32,'192.168.1.3',1256)
    thread.start()
    threads.append(thread)
    threadcount = threadcount + 1

waitcount = 0
t = time.time()
print("start at ",int(round(t*1000)))
while waitcount < threadcount:
    threads[waitcount].join()
    waitcount = waitcount + 1

t = time.time()
print("end at ",int(round(t*1000)))