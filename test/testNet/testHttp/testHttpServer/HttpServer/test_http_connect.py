import socket
import threading
import time
import http.client

while 1:
    client = http.client.HTTPConnection("192.168.1.9:1256")
    print("trace1")
    client.request("GET","/index")
    print("trace2")
    r1 = client.getresponse()
    print(r1.read().decode("utf-8"))
    r1.close()