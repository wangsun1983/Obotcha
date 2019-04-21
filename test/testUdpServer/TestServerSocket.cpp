#include "UdpServer.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(ServerListener) IMPLEMENTS(SocketListener) {
public:
    void onAccept(int fd,SocketPacket pack) {
      printf("on accept \n");
    }

    void onDisconnect(int fd){
      printf("onDisconnect \n");
    }

    void onConnect(int fd) {
      printf("onConnect \n");
    }
};

int main() {
  ServerListener listener = createServerListener();
  UdpServer server = createUdpServer("192.168.1.10",1234,listener);
  server->start();
  while(1) {}
}
