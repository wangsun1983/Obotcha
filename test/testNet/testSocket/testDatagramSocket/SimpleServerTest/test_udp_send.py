import socket

s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
s.connect(("192.168.1.9",1222))
while True:
    s.send(str("hello server").encode("utf-8"))
    response = s.recv(1024).decode()
    printf("response is " + response)
    time.sleep(1)