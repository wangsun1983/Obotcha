from websocket import create_connection
import threading

ws = create_connection("ws://192.168.1.3:1114/mytest")
msg = "Hello, World"
ws.send(msg)
ws.close()