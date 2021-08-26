import socket
import time

s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
s.connect(("127.0.0.1",1222))
print "123"
s.send(str("hello server").encode("utf-8"))

sendData = s.recv(1024).decode()
print "222"
count = 0

while (count < 50):
    s.send(sendData)
    time.sleep(0.01)
    count = count + 1

print("send complete")