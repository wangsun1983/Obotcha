import socket
#创建socket对象
#SOCK_DGRAM  udp模式
s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
s.bind(("192.168.1.6",1222)) #绑定服务器的ip和端口
while True:
    receive_data,client = s.recvfrom(1024);
    print(receive_data.decode("utf-8"))# decode()解码收到的字节
    s.sendto(str("hello world").encode("utf-8"),client)
    time.sleep(1)