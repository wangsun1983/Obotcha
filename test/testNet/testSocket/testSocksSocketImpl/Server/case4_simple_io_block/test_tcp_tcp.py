import socket
import time

s=socket.socket()
s.connect(("127.0.0.1",1222))
print "123"

count = 0

while (count < 1024):
    s.send(str("hello server").encode("utf-8"))
    time.sleep(0.10)
    count = count + 1

print("send complete")