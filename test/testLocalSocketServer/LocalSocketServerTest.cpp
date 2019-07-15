#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "LocalSocketServer.hpp"
#include "SocketListener.hpp"
#include "NetUtils.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(ServerListener) IMPLEMENTS(SocketListener) {
public:
    void onAccept(int fd,ByteArray pack) {
      printf("on accept pack is %s \n",pack->toValue());
    }

    void onDisconnect(int fd){
      printf("onDisconnect \n");
    }

    void onConnect(int fd,String domain){
      printf("onConnect,domain is %s,fd is %d \n",domain->toChars(),fd);
      ByteArray arr = createByteArray(createString("nihao from server"));
      st(NetUtils)::sendTcpPacket(fd,arr);
    }
};

DECLARE_SIMPLE_CLASS(CloseThread) EXTENDS(Thread) {
public:
    _CloseThread(LocalSocketServer c) {
        server = c;
    }

    void run() {
        printf("start thread \n");
        sleep(5);
        printf("start release \n");
        server->release();
        printf("start finished \n");
    }

private:
    LocalSocketServer server;    
};

int main() {
  printf("localsocketserver start \n");
  ServerListener listener = createServerListener();
  LocalSocketServer server = createLocalSocketServer("/tmp/abcd",listener);
  server->start();
  CloseThread t = createCloseThread(server);
  t->start();
  printf("localsocketserver trace \n");
  while(1) {}
}
