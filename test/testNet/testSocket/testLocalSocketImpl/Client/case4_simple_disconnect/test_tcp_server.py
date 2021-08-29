from socket import *
import sys
import threading
import socket
import time
import os
import socket

class ShutDownThread(threading.Thread):
    def __init__(self,c,s):
        threading.Thread.__init__(self)
        self.mconn = c
        self.maddr = s

    def run(self):
        self.mconn.close()


server_address = 'case4_socket'
 
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

threads= []
s.listen(256)
index = 0

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