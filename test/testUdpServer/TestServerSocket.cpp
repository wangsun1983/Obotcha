#include "UdpServer.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Thread.hpp"
#include "NetUtils.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(ServerListener) IMPLEMENTS(SocketListener) {
public:
    void onAccept(int fd,String ip,int port,ByteArray pack) {
      printf("on accept pack is %s \n",pack->toValue());
      printf("on accept ip is %s,port is %d \n",ip->toChars(),port);

      ByteArray sendPacket = createByteArray(createString("hahahah hello from server!!!"));
      st(NetUtils)::sendUdpPacket(fd,ip,port,sendPacket);
    }

    void onDisconnect(int fd){
      printf("onDisconnect \n");
    }

    void onConnect(int fd,String ip,int port) {
      printf("onConnect,ip is %s,port is %d,fd is %d \n",ip->toChars(),port,fd);
      ByteArray sendPacket = createByteArray(createString("nihao from server"));
      st(NetUtils)::sendTcpPacket(fd,sendPacket);
    }

    void onConnect(int fd,String domain) {}
};

DECLARE_SIMPLE_CLASS(CloseThread) EXTENDS(Thread) {
public:
    _CloseThread(UdpServer c) {
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
    UdpServer server;    
};

//void testTcpServer() {
//  TcpServer server = createTcpServer(1111,createServerListener());
  //CloseThread t = createCloseThread(server);
  //t->start();

//  server->start();
//}

int main() {
  ServerListener listener = createServerListener();
  UdpServer server = createUdpServer(1111,listener);
  //CloseThread t = createCloseThread(server);
  //t->start();

  server->start();
  //testTcpServer();
  while(1) {}
  printf("end main!!!! \n");
}
