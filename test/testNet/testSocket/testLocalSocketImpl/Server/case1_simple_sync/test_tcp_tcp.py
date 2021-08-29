import socket
import time

# Create a UDS socket
s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
 
# Connect the socket to the port where the server is listening
server_address = 'case1_socket'

s.connect(server_address)

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