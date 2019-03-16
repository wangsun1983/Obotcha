#include "ServerSocket.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

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
  ServerSocket server = createServerSocket("192.168.43.252",8888,listener);
  server->start();
}
