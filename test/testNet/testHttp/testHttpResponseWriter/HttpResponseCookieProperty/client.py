import socket
import threading
import time
import http.client
import requests
import os

#while 1:
r = requests.get("http://127.0.0.1:1256/index")
payload={}
for c in r.cookies: 
    #print(c.name, c.value)
    payload[c.name] = c.value

print(payload)
r = requests.get("http://127.0.0.1:1256/apq",data=payload)

#get cookie
print("trace4")