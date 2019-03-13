#include "ServerSocket.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"



DECLARE_SIMPLE_CLASS(ServerListener) IMPLEMENTS(SocketListener) {
public:
    void onAccept(int fd,SocketPacket pack) {
      printf("on accept %s \n",pack->data());

    }

    void onDisconnect(int fd){
      printf("onDisconnect \n");
    }

    void onConnect(int fd) {
      printf("onConnect \n");
      String abc = "hello hahah";
      send(fd,abc->toChars(),abc->size(),0);
    }
};

int main() {
  ServerListener listener = createServerListener();
  ServerSocket server = createServerSocket("192.168.1.8",8888,listener);
  server->start();
}
