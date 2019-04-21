
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "UdpClient.hpp"

using namespace obotcha;

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
  UdpClient client = createUdpClient("192.168.1.10",1234,createClientServer());
  client->start();
  //while(1) {
//
  //}
}
