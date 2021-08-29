from socket import *
import sys
import threading
import socket
import time
import os
import socket

class SendThread(threading.Thread):
    def __init__(self,c,s):
        threading.Thread.__init__(self)
        self.mconn = c
        self.maddr = s
        #print "new connection,fd is " + str(self.mconn.fileno())

    def run(self):
        count = 1024*32 - 1
        while count > 0:
            #print "send data,str is " + str(count).encode("utf-8") + ",fd is " + str(self.mconn.fileno())
            self.mconn.send(str(count).encode("utf-8"))
            if(count != 1):
                data = self.mconn.recv(1024)
            count = count -1
        print "send finished"
        self.mconn.close()


server_address = 'case3_socket'
 
# Make sure the socket does not already exist
try:
    os.unlink(server_address)
except OSError:
    if os.path.exists(server_address):
        raise
# Create a UDS socket
s = socket.socket(socket.AF_UNIX,socket.SOCK_STREAM)
# Bind the socket to the port
s.bind(server_address)

index = 0
print "start test"

threads= []
s.listen(256)

while index < 128:    
    #print "trace1"
    myconn,myaddr = s.accept()
    t = SendThread(myconn,myaddr);
    t.start()
    threads.append(t)
    index = index + 1

for t in threads:
    #print "start join"
    t.join()

print "finish!!!"