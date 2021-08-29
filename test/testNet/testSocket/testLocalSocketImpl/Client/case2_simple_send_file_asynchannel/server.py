from socket import *
import sys
import select
import os
import socket
import time

server_address = 'case2_socket'
 
# Make sure the socket does not already exist
try:
    os.unlink(server_address)
except OSError:
    if os.path.exists(server_address):
        raise
# Create a UDS socket
sock = socket.socket(socket.AF_UNIX,socket.SOCK_STREAM)
# Bind the socket to the port
sock.bind(server_address)
print "start"
path = "file"

f = open("file",'wb')
sock.listen(5)
conn,address = sock.accept()
conn.settimeout(5)
print "trace1"
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