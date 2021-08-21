import socket

s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
s.bind(("127.0.0.1",1213))
count = 0
receive_data,client = s.recvfrom(1024)
print("hjjjjj")

while count < 50:
    print(receive_data.decode("utf-8"))
    s.sendto(receive_data.decode("utf-8"),client)
    count = count + 1

client.close()
s.close()
exit()