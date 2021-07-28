import socket
import threading
import time
import http
import requests
from requests_toolbelt.multipart.encoder import MultipartEncoder
import random
import os
import _thread

# 为线程定义一个函数
def do_connect( ip, port):
   address = (ip,port)
   count = 1024
   while count > 0:
        s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        s.connect(address)
        s.sendall(str("hello server").encode("utf-8"))
        s.close()
        count = count - 1

try:
   _thread.start_new_thread( do_connect, ("192.168.1.9", 1222))
   _thread.start_new_thread( do_connect, ("192.168.1.9", 1223))
   _thread.start_new_thread( do_connect, ("192.168.1.9", 1224))
except:
   print ("Error: 无法启动线程")

while 1:
    pass