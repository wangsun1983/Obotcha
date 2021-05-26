import socket
#创建socket对象
#SOCK_DGRAM  udp模式
s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
s.bind(("192.168.1.6",1222)) #绑定服务器的ip和端口
data=s.recv(1024) #一次接收1024字节
print(data.decode())# decode()解码收到的字节