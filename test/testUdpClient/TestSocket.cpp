
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "UdpClient.hpp"
#include "Thread.hpp"
#include "NetUtils.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(ClientServer) IMPLEMENTS(SocketListener) {
public:
    void onAccept(int fd,String ip,int port,ByteArray pack) {
      printf("on accept pack is %s\n,ip is %s,port is %d",pack->toValue(),ip->toChars(),port);
      ByteArray packet = createByteArray(createString("hahahah hello from client!!!"));
      st(NetUtils)::sendUdpPacket(fd,ip,port,packet);
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
    _CloseThread(UdpClient c) {
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
    UdpClient server;    
};



int main() {
  printf("udp client start \n");
  UdpClient client = createUdpClient("192.168.43.90",1111,createClientServer());
  //CloseThread t = createCloseThread(client);
  //t->start();
  //testTcpClient();
  client->start();
  printf("udp client start1 \n");

  ByteArray arr = createByteArray(createString("nihao from client"));
  client->send(arr);
  printf("udp client start2 \n");

  printf("main end!!!! \n");
  while(1) {
  
  }
}
