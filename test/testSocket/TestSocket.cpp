#include "ServerSocket.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Socket.hpp"

DECLARE_SIMPLE_CLASS(ClientServer) IMPLEMENTS(SocketListener) {
public:
    void onAccept(int fd,SocketPacket pack) {
      printf("on accept pack is %s\n",pack->data());
    }

    void onDisconnect(int fd){
      printf("onDisconnect \n");
    }

    void onConnect(int fd) {
      printf("onConnect \n");
    }
};

int main() {
  Socket sock = createSocket("192.168.1.8",8888,createClientServer());
  sock->start();
  while(1) {

  }
}
