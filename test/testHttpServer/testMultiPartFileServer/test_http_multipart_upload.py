import socket
import threading
import time
import http
import requests
from requests_toolbelt.multipart.encoder import MultipartEncoder
import random
import os

while 1:
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:50.0) Gecko/20100101 Firefox/50.0',
    }


    multipart_encoder = MultipartEncoder(
        fields = {
            'file': (os.path.basename("abc.jpg"), open("./abc.jpg", 'rb'), 'multipart/form-data'),
            'save_name': 'abc.jpg',
            'key1':'value1'
        },
        boundary = '-----------------------------' + str(random.randint(1e28, 1e29 - 1))
    )

    headers['Content-Type'] = multipart_encoder.content_type
    responseStr = requests.post('http://192.168.1.10:1256', data=multipart_encoder, headers=headers)
    print("get response")
    #print(response.text)