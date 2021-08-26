from socket import *
import sys
import select
import os
import socket
import time

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM) 

s.bind(("127.0.0.1", 1234))

print "start"
path = "file"

f = open("file",'wb')
s.listen(5)
conn,address = s.accept()
conn.settimeout(5)

while True:
    #print "trace1"
    data = conn.recv(1024)
    f.write(data)
    f.flush();
    time.sleep(0.01)
    if not data:
        print "trace2"
        break

f.close()
s.close()
conn.close()

print "File Donwloaded"