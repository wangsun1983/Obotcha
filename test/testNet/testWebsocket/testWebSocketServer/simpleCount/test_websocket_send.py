from websocket import create_connection

count = 1024*32
while count > 0:
  ws = create_connection("ws://192.168.1.5:1111")
  msg = "Hello, World"
  #print("发送消息：%s" % msg)
  ws.send(msg)
  # print("发送中...")
  #result = ws.recv()
  #print("返回结果：%s" % result)
  ws.close()
  count = count - 1

print("test finished")