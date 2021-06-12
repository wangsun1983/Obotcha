import socket
import threading
import time
import http.client
import requests
import os

count = 1
#while 1:
print("trace1")
while 1:
    r = requests.get("http://192.168.1.9:1123/index")
    filename = str(count)+".txt"
    print("trace2")
    with open(os.path.join(os.path.dirname(os.path.abspath("__file__")),filename),"wb") as f:
        f.write(r.content)
    print("trace3")
    count = count + 1
    r.close()
    print("trace4")