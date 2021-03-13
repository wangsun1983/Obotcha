import socket
import threading
import time

class ConnectThread(threading.Thread):
    def __init__(self,threadID,loopcount,sendcount,ip,port):
        threading.Thread.__init__(self)
        self.id = threadID
        self.mytid = threading
        self.loopcount = loopcount
        self.address = (ip,port)
        self.sendcount = sendcount

    def run(self):
        count = self.loopcount
        while count > 0:
            s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
            s.connect(self.address)
            s.send((str(self.id) +" | hello"+ str(count)).encode("utf-8"))
            response = s.recv(1024).decode()
            if response != (str(self.id) + " | hello"+str(count)):
                print("error data,response is " + response + ",test data is " + "hello" + str(count))
            s.close()
            count = count - 1

#start test
threadcount = 0
threads = []
while threadcount < 12:
    thread = ConnectThread(threadcount,1024,32,'192.168.1.3',1234)
    thread.start()
    threads.append(thread)
    threadcount = threadcount + 1

waitcount = 0
t = time.time()
print("start at ",int(round(t*1000)))
while waitcount < threadcount:
    threads[waitcount].join()
    waitcount = waitcount + 1

t = time.time()
print("end at ",int(round(t*1000)))