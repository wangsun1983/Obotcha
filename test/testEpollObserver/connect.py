import socket               # 导入 socket 模块
import threading
import time

class ConnectThread (threading.Thread):
    def __init__(self, threadID):
        threading.Thread.__init__(self)
        self.threadID = threadID

    def run(self):
        count = 1024;
        while count > 0:
            simpleConnect()
            count = count-1
        print("i complete task,thread id is ",self.threadID)

def simpleConnect() :
    s = socket.socket()
    host = socket.gethostname()
    port = 1222
    s.connect((host, port))
    msg = "hello world"
    s.send(msg.encode("utf-8"))
    time.sleep(0.01)
    s.close()

def simpleConnectAndSend():
    s = socket.socket() 
    host = socket.gethostname() 
    port = 1222 
    s.connect((host, port))
    time.sleep(0.01)
    s.send("hello world")
    s.close()

#testConnect
threadcount = 0
threads = []
print("trace1")
while threadcount < 16:
    print("trace2,count is ",threadcount)
    thread = ConnectThread(threadcount)
    thread.start()
    threads.append(thread)
    threadcount = threadcount + 1

waitcount = 0
t = time.time()
print (int(round(t * 1000)))
while waitcount < threadcount:
    threads[waitcount].join()
    waitcount = waitcount + 1

t = time.time()
print (int(round(t * 1000)))

print("finish !!!!")
