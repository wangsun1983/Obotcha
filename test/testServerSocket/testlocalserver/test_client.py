import socket

UNIX_SOCK_PIPE_PATH = "/tmp/mytest.sock"  
sock=socket.socket(socket.AF_UNIX,socket.SOCK_STREAM)
sock.connect(UNIX_SOCK_PIPE_PATH)
print(sock.send(str("hello").encode("utf-8")))
sock.close()
