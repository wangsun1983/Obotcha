from websocket import create_connection
import threading

ws = create_connection("ws://127.0.0.1:1114/mytest")
msg = "Hello, World"
ws.send(msg)
ws.close()