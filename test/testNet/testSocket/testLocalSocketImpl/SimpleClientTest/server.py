import socket
import sys
import os
 
server_address = 'mysock'
 
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
 
# Listen for incoming connections
sock.listen(1)
print("start listen!!!")


# Wait for a connection
connection, client_address = sock.accept()
count = 0
while (count < 50):
    print("start get an acception!!!")
    msg = "hello client"
    connection.sendall(msg.encode())
    count = count + 1

connection.close()