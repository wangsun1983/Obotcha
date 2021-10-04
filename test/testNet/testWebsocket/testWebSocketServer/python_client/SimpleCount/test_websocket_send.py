from websocket import create_connection

count = 0

while count < 1024*32:
    ws = create_connection("ws://127.0.0.1:1111/mytest")
    msg = "Hello, World"
    ws.send(msg)
    ws.close()
    count = count+1

print("test finished")