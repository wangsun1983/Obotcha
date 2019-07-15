#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "LocalSocketClient.hpp"
#include "SocketListener.hpp"


using namespace obotcha;

DECLARE_SIMPLE_CLASS(ClientServer) IMPLEMENTS(SocketListener) {
public:
    void onAccept(int fd,ByteArray pack) {
      printf("on accept pack is %s\n",pack->toValue());
    }

    void onDisconnect(int fd){
      printf("onDisconnect \n");
    }

    void onConnect(int fd,String domain) {
      printf("onConnect \n");
    }
};


int main() {
  printf("---[LocalSocketClient Test Start]--- \n");
  LocalSocketClient client = createLocalSocketClient("/tmp/abcd",createClientServer());
  client->start();
  char *p = "hello world";
  ByteArray arr = createByteArray(strlen(p) + 1);
  memcpy(arr->toValue(),p,strlen(p));
  printf("wangsl,send content %s \n",arr->toValue());
  client->send(arr);

  while(1) {}
}
