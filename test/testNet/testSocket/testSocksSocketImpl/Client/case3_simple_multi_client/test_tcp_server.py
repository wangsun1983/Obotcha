from socket import *
import sys
import threading
import socket

class SendThread(threading.Thread):
    def __init__(self, conn):
        threading.Thread.__init__(self)
        self.conn = conn

    def do_send():
        count = 1024*32
        while count > 0:
            conn.sendAll(str(count).encode("utf-8"))
            count = count -1
        conn.close()

host="127.0.0.1"
port = 1234

s = socket.socket() 
s.bind((host,port))
index = 0
print "trace1"

threads= []

while index < 128:
    s.listen(5)
    print "trace1"
    conn,address = s.accept()
    threads.append(SendThread(conn))
    threads[index].start()
    index = index + 1

for t in threads:
    t.join()

print "finish!!!"