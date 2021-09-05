import socket
import threading
import time
import http.client

count = 0

#sudo sysctl -w net.ipv4.tcp_timestamps=1

class ConnectThread(threading.Thread):
    def __init__(self,id):
        threading.Thread.__init__(self)
        self.threadid = id;

    def run(self):
        self.count = 0
        self.client = http.client.HTTPConnection("127.0.0.1:1256")
        while count < 1024*32:
            try:
                print("trace1,id" + str(self.threadid))
                params = str(self.threadid)
                self.client.request("GET","/index",params)
                print("trace2,id" + str(self.threadid))
                #response.read()
                self.resp = self.client.getresponse()
                data = self.resp.read().decode('utf-8')
                print("trace3,id" + str(self.threadid))

                #self.r1.read();
                #print(r1.read().decode("utf-8"))
                #r1.close()
                #client.close();
                #time.sleep(0.01);
                self.count = self.count + 1
            except OSError:
                print("no port can be used!!!!")
                time.sleep(10)
        self.client.close()
print("start!!!")

threads= []
index = 0
while index < 128:    
    #print "trace1"
    t = ConnectThread(index);
    t.start()
    threads.append(t)
    index = index + 1

for t in threads:
    t.join()

print("finish!!!")