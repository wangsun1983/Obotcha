from socket import *
import sys
import select
import os
import time
import socket

host="127.0.0.1"

port = 1233

s=socket.socket()
s.connect(("127.0.0.1",2345))

buf=4096*32
f = open("file",'wb')

print "cccc"
with open('data', 'r') as fp:
    while True:
        print "aaaa"
        data = fp.read(1024*4)
        s.send(data)
        time.sleep(0.1)
        if not data:
            break;


print "Upload Donwloaded"