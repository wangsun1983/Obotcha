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

  printf("---[UdpServer Test Start]--- \n");

  while(1) {
    ServerListener listener = createServerListener();
    UdpServer server = createUdpServer(1111,listener);
    printf("---[UdpServer Test {Construct()} case1] [Success]--- \n");
    break;
  }

  while(1) {
    ServerListener listener = createServerListener();
    UdpServer server = createUdpServer(1111,listener);
    server->start();
    printf("---[UdpServer Test {start()} case1] [Success]--- \n");
    break;
  }

  while(1) {
    ServerListener listener = createServerListener();
    UdpServer server = createUdpServer(1111,listener);
    server->start();
    sleep(1);
    server->release();
    printf("---[UdpServer Test {release()} case1] [Success]--- \n");
    break;
  }

  while(1) {
    ServerListener listener = createServerListener();
    UdpServer server = createUdpServer(1111,listener);
    server->start();

    UdpClient client = createUdpClient(1111,nullptr);
    String str = createString("hello world ");
    client->send(createByteArray(str));
    sleep(1);

    String accept = listener->getAcceptStr();
    if(accept == nullptr || !accept->equals(str)) {
      printf("---[UdpServer Test {getAccept()} case1] [Fail]--- \n");
      break;
    }
    
    printf("---[UdpServer Test {getAccept()} case1] [Success]--- \n");
    break;
  }


  //send
  while(1) {
    printf("start 0");
    ServerListener listener = createServerListener();
    UdpServer server = createUdpServer(1111,listener);
    printf("start 1");
    server->start();
    printf("start 2");

    ClientListener mClientListener = createClientListener();
    UdpClient client = createUdpClient(1111,mClientListener);
    client->start();
    String str = createString("nihaoaaaaaaaaa ");

    int ret = client->send(createByteArray(str));
    printf("ret is %d,error is %s \n",ret,strerror(errno));

    String accept = listener->getAcceptStr();
    if(accept == nullptr || !accept->equals(str)) {
      printf("---[UdpServer Test {send()} case1] [Fail]--- \n");
      break;
    }

    int fd = listener->getClientFd();
    int port = listener->getClientPort();
    printf("fd is %d \n",fd);
    String ss = createString("my test");
    ret = st(NetUtils)::sendUdpPacket(createString("127.0.0.1"),port,createByteArray(ss));

    sleep(1);

    String mmaccept = mClientListener->getAcceptStr();
    if(mmaccept == nullptr || !mmaccept->equals(ss)) {
      printf("---[UdpServer Test {send()} case2] [Fail]--- \n");
      break;
    }

    printf("---[UdpServer Test {send()} case2] [Success]--- \n");
    break;
  }


  sleep(10);

 }
