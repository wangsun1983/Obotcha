import socket
import threading
import time
import http
import requests
from requests_toolbelt.multipart.encoder import MultipartEncoder
import random
import os


class UploadThread(threading.Thread):
    def __init__(self,id):
        threading.Thread.__init__(self)
        self.threadid = id;

    def run(self):
        count = 0
        while count < 16:
            headers = {
                'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:50.0) Gecko/20100101 Firefox/50.0',
            }


            multipart_encoder = MultipartEncoder(
                fields = {
                    'file': (os.path.basename("data"), open("./data", 'rb'), 'multipart/form-data'),
                    'save_name': 'data',
                    'key1':'value1'
                },
                boundary = '-----------------------------' + str(random.randint(1e28, 1e29 - 1))
            )

            headers['Content-Type'] = multipart_encoder.content_type

            print("send start")
            requests.post('http://127.0.0.1:1256', data=multipart_encoder, headers=headers)
            #responseStr.read();
            count = count + 1
            print("send complete")

threads= []
index = 0
while index < 128:    
    #print "trace1"
    t = UploadThread(index);
    t.start()
    threads.append(t)
    index = index + 1

for t in threads:
    t.join()

print("finish!!!")
print("get response")
    #print(response.text)