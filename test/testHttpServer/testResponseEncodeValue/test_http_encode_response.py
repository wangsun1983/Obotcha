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
    r = requests.get("http://192.168.1.9:1124/index")
    print(r.text)
    print("trace4")