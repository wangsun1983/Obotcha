import socket

s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
s.sendto("hello".encode(),("192.168.1.9",1222))
print("send finished")