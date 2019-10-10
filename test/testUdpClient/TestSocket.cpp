#include "UdpServer.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Thread.hpp"
#include "NetUtils.hpp"
#include "UdpClient.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(ServerListener) IMPLEMENTS(SocketListener) {
public:
    _ServerListener() {
        mAcceptMutex = createMutex();
        mCond = createCondition();
    }

    void onAccept(int fd,String ip,int port,ByteArray pack) {
      printf("on accept pack is %s \n",pack->toString()->toChars());
      printf("on accept ip is %s,port is %d \n",ip->toChars(),port);

      //ByteArray sendPacket = createByteArray(createString("hahahah hello from server!!!"));
      //st(NetUtils)::sendUdpPacket(ip,port,sendPacket);
      mAccept = pack->toString();
      mFd = fd;
      mPort = port;
      mCond->notify();
    }

    void onDisconnect(int fd){
      printf("onDisconnect \n");
    }

    void onConnect(int fd,String ip,int port) {
      printf("onConnect,ip is %s,port is %d,fd is %d \n",ip->toChars(),port,fd);
      //ByteArray sendPacket = createByteArray(createString("nihao from server"));
      //st(NetUtils)::sendTcpPacket(fd,sendPacket);
      mFd = fd;

    }

    void onConnect(int fd,String domain) {}

    String getAcceptStr() {
      if(mAccept != nullptr) {
        return mAccept;
      }

      AutoMutex ll(mAcceptMutex);
      mCond->wait(mAcceptMutex);
      return mAccept;
    }

    int getClientFd() {
      return mFd;
    }

    int getClientPort() {
      return mPort;
    }

private:
    Mutex mAcceptMutex;
    String mAccept;
    Condition mCond;

    int mFd;
    int mPort;
};

DECLARE_SIMPLE_CLASS(ClientListener) IMPLEMENTS(SocketListener) {
public:
    _ClientListener() {
        mAcceptMutex = createMutex();
        mCond = createCondition();
    }

    void onAccept(int fd,String ip,int port,ByteArray pack) {
        printf("client accept is %s \n",pack->toString()->toChars());
        mAccept = pack->toString();
        mCond->notify();
    }

    void onDisconnect(int fd){
        printf("onDisconnect \n");
    }

    void onConnect(int fd,String ip,int port) {
        mfd = fd;
    }

    void onConnect(int fd,String domain) {}

    String getAcceptStr() {
        if(mAccept != nullptr) {
          return mAccept;
        }

        AutoMutex ll(mAcceptMutex);
        mCond->wait(mAcceptMutex);
        return mAccept;
    }

private:
    int mfd;

    Mutex mAcceptMutex;
    String mAccept;
    Condition mCond;
};


int main() {
  printf("---[UdpClient Test Start]--- \n");

  while(1) {
    {
        //ClientListener l = createClientListener();
        UdpClient client = createUdpClient(1111,nullptr);
        //Pipe p = createPipe();
        //p->init();
    }
    sleep(5);
    printf("---[UdpClient Test {Construct()} case1] [Success]--- \n");
    break;
  }


  while(1) {
    {
        //ClientListener l = createClientListener();
        UdpClient client = createUdpClient(1111,nullptr);
        client->start();
    }
    sleep(5);
    printf("---[UdpClient Test {start()} case1] [Success]--- \n");
    break;
  }

  while(1) {
    ClientListener l = createClientListener();
    UdpClient client = createUdpClient(1111,l);
    client->release();
    printf("---[UdpClient Test {release()} case1] [Success]--- \n");

    UdpClient client2 = createUdpClient(1111,l);
    client2->start();
    client2->release();
    printf("---[UdpClient Test {release()} case2] [Success]--- \n");
    break;
  }


  while(1) {
    ServerListener serverlistener = createServerListener();
    UdpServer server = createUdpServer(1111,serverlistener);
    server->start();

    ClientListener clientlistener = createClientListener();
    UdpClient client = createUdpClient(1111,clientlistener);
    client->start();

    String str = createString("nihao,hahaha");
    client->send(createByteArray(str));

    String accept = serverlistener->getAcceptStr();
    if(accept == nullptr || !accept->equals(str)) {
      printf("---[UdpClient Test {send()} case1] [Fail]--- \n");
      break;
    }

    int clientfd = serverlistener->getClientFd();
    int port = serverlistener->getClientPort();
    printf("clientfd is %d \n",clientfd);
    String ss = createString("my test");
    int ret = st(NetUtils)::sendUdpPacket(createString("127.0.0.1"),port,createByteArray(ss));
    sleep(1);
    String accept2 = clientlistener->getAcceptStr();
    if(accept2 == nullptr || !accept2->equals(ss)) {
      printf("---[UdpClient Test {send()} case2] [Fail]--- \n");
      break;
    }

    printf("---[UdpClient Test {send()} case3] [Success]--- \n");
    break;
  }

  sleep(10);
}
