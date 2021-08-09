import socket
import sys
import time
 
# Create a UDS socket
sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
 
# Connect the socket to the port where the server is listening
server_address = './mysock'


sock.connect(server_address)


# Send data
message = 'hello server'
count = 0
while (count < 50):
    sock.sendall(message.encode())
    count = count + 1

sock.close()
