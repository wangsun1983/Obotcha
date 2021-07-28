import socket
import sys
import time
 
# Create a UDS socket
sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
 
# Connect the socket to the port where the server is listening
server_address = './mysock'


sock.connect(server_address)


# Send data
message = 'This is the message.  It will be repeated.'
sock.sendall(message.encode())


amount_received = 0
amount_expected = len(message)

#while amount_received < amount_expected:
#    data = sock.recv(16)
#    amount_received += len(data)
 
time.sleep(5)
sock.close()
