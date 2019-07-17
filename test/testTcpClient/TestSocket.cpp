
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "TcpClient.hpp"
#include "Thread.hpp"
#include "System.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(ClientServer) IMPLEMENTS(SocketListener) {
public:
    void onAccept(int fd,String ip,int port,ByteArray pack) {
      printf("on accept pack is %s\n",pack->toValue());
      if(ip != nullptr) {
          printf("accept ip is %s,port is %d \n",ip->toChars(),port);
      }
    }

    void onDisconnect(int fd){
      printf("onDisconnect \n");
    }

    void onConnect(int fd,String ip,int port) {
      printf("onConnect,ip is %s,port is %d,fd is %d \n",ip->toChars(),port,fd);

    }

    void onConnect(int fd,String domain) {}
};

DECLARE_SIMPLE_CLASS(CloseThread) EXTENDS(Thread) {
public:
    _CloseThread(TcpClient c) {
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
    TcpClient server;    
};



int main() {
  TcpClient client = createTcpClient("192.168.43.90",1111,createClientServer());
  //CloseThread t = createCloseThread(client);
  //t->start();
  //testTcpClient();
  client->start();

  ByteArray arr = createByteArray(createString("nihao from client"));
  client->send(arr);

  long t = st(System)::currentTimeMillis();
  printf("start wait \n");
  client->wait();
  printf("start wait end : %ld \n",st(System)::currentTimeMillis() - t);
  //client->release();
  //printf("main end!!!! \n");
  //while(1) {
  //
  //}
}
