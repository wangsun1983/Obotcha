#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "LocalSocketServer.hpp"
#include "SocketListener.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(ServerListener) IMPLEMENTS(SocketListener) {
public:
    void onAccept(int fd,SocketPacket pack) {
      printf("on accept pack is %s \n",pack->data());
    }

    void onDisconnect(int fd){
      printf("onDisconnect \n");
    }

    void onConnect(int fd) {
      printf("onConnect \n");
    }
};

int main() {
  printf("localsocketserver start \n");
  ServerListener listener = createServerListener();
  LocalSocketServer server = createLocalSocketServer("/tmp/abcd",listener);
  server->start();
  while(1) {}
}
