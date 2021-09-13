import socket
import threading
import time
import http.client

count = 0

while count < 1:
    client = http.client.HTTPConnection("127.0.0.1:1260")
    client.request("GET","/index")
    r1 = client.getresponse()
    print(r1.read().decode("utf-8"))
    r1.close()
    client.close();
    count = count + 1