import socket
import time

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server_address = ("192.168.1.6", 1234)
s.bind(server_address)
s.listen(5)
print('Waiting for connection...')

client,addr = s.accept()
with open("./data.img","ab") as f:
 while True:
  print("start rcv data")
  data = client.recv(1024)
  print("i receive data")
  if not data:
   break;
  f.write(data)
  f.flush()

f.close()
print("recv complete")