from socket import *
import sys
import threading
import socket
import time

class ShutDownThread(threading.Thread):
    def __init__(self,c,s):
        threading.Thread.__init__(self)
        self.mconn = c
        self.maddr = s

    def run(self):
        self.mconn.close()


host="127.0.0.1"
port = 1234

s = socket.socket() 
s.bind((host,port))
index = 0
print "start test"

threads= []
s.listen(256)

while index < 1024*32:    
    #print "trace1"
    myconn,myaddr = s.accept()
    t = ShutDownThread(myconn,myaddr);
    t.start()
    threads.append(t)
    index = index + 1

for t in threads:
    #print "start join"
    t.join()

print "finish!!!"