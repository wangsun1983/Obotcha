import socket
import threading
import time
import http
import http.client
import urllib.parse

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
            h1 = http.client.HTTPConnection("192.168.1.3",1256)
            headers = {'Referer': 'http://t66y.com/index.php',
                        'Accept - Encoding': 'gzip, deflate',
                        'Accept - Language': 'zh - CN, zh;q = 0.9',}
            params = str(self.id) + " thread,count is " + str(count)
            
            h1.request("GET", "/index", params, headers)
            
            r1 = h1.getresponse()
            data = r1.read().decode()
            print(data)
            if data != str(self.id) + " thread,count is " + str(count):
                print("error response")

            h1.close()
            time.sleep(0.01)
            count = count - 1

#start test
threadcount = 0
threads = []
while threadcount < 12:
    thread = ConnectThread(threadcount,32,32,'192.168.1.3',1256)
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