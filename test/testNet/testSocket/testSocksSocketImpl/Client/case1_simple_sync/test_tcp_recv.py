import socket

s = socket.socket() 
host = socket.gethostname()
port = 1213

s.bind(("127.0.0.1", port))

s.listen(5)
c,client = s.accept()

receive_data = c.recv(1024)
count = 0

while count < 50:
    print(receive_data.decode("utf-8"))
    c.sendto(receive_data.decode("utf-8"),client)
    count = count + 1

c.close()
s.close()

exit()