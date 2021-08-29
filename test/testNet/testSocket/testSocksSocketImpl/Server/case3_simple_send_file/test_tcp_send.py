from socket import *
import sys
import select
import os
import socket

host="127.0.0.1"

port = 1233

s=socket.socket()
s.connect(("127.0.0.1",1233))

buf=4096*32
f = open("file",'wb')

print "cccc"
with open('data', 'r') as fp:
    while True:
        data = fp.read(1024*4)
        s.send(data)
        
        if not data:
            break;

        data1 = s.recv(1024)


print "Upload Donwloaded"