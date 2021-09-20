import socket
import threading
import time
import http.client
import requests
import os

#while 1:
headers = {"tag1":"value1","tag2":"value2"}
r = requests.get("http://127.0.0.1:1124/index",headers = headers)
print(r.text)
print("trace4")