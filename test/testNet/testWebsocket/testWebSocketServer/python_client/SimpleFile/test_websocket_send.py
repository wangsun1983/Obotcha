from websocket import create_connection
import threading


ws = create_connection("ws://127.0.0.1:1111/mytest")
msg = "Hello, World"

with open('./tmp/data', 'r') as fp:
    while True:
        data = fp.read(1024*4)
        ws.send(data)
        
        if not data:
            break;

ws.close()



print("test finished")