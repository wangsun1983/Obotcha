#include "UdpServer.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Thread.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(ServerListener) IMPLEMENTS(SocketListener) {
public:
    _ServerListener() {
    }

    void onDataReceived(SocketResponser r,ByteArray pack){
      //printf("on accept pack is %s \n",pack->toString()->toChars());
      //printf("on accept ip is %s,port is %d \n",ip->toChars(),port);

      //ByteArray sendPacket = createByteArray(createString("hahahah hello from server!!!"));
      //st(NetUtils)::sendUdpPacket(ip,port,sendPacket);
      printf("r fd is %d \n",r->getFd());
      String mAccept = pack->toString();
      printf("mAccept is %s \n",mAccept->toChars());
    }

    void onDisconnect(SocketResponser r){
      printf("onDisconnect \n");
    }

    void onConnect(SocketResponser r) {
      printf("onConnect \n");
      //printf("onConnect,ip is %s,port is %d,fd is %d \n",ip->toChars(),port,fd);
      //ByteArray sendPacket = createByteArray(createString("nihao from server"));
      //st(NetUtils)::sendTcpPacket(fd,sendPacket);
      //mFd = fd;

    }

    void onConnect(int fd,String domain) {}
    void onTimeout(){}

private:

    int mFd;
    int mPort;
};


int main() {

  printf("---[UdpServer Test Start]--- \n");

  while(1) {
    ServerListener listener = createServerListener();
    UdpServer server = createUdpServer(1222,listener);
    server->start();
    printf("---[UdpServer Test {Construct()} case1] [Success]--- \n");
    while(1) {
      sleep(10);
    }
  }
  


  sleep(10);

 }
