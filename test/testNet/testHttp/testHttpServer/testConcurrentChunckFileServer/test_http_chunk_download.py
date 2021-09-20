import socket
import threading
import time
import http.client
import requests
import os


class DownloadThread(threading.Thread):
    def __init__(self,id):
        threading.Thread.__init__(self)
        self.threadid = id;

    def run(self):
        count = 0
        while count < 16:
            r = requests.get("http://127.0.0.1:1123/index")
            filename = "./tmp/"+"_id_" + str(self.threadid) + "_" + str(count)
            print("trace2")
            with open(os.path.join(os.path.dirname(os.path.abspath("__file__")),filename),"wb") as f:
                f.write(r.content)
            print("trace3")
            count = count + 1
            r.close()
            print("send complete")

threads= []
index = 0
while index < 128:    
    #print "trace1"
    t = DownloadThread(index);
    t.start()
    threads.append(t)
    index = index + 1

for t in threads:
    t.join()

print("finish!!!")
print("get response")
