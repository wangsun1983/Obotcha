
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "TcpClient.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "AsyncTcpClient.hpp"
#include "NetUtils.hpp"
#include "TcpServer.hpp"

using namespace obotcha;

//server
DECLARE_CLASS(ServerListener) IMPLEMENTS(SocketListener) {
public:
    _ServerListener() {
        clientfd = 0;
        mutex = createMutex();
        cond = createCondition();

        acceptMutex = createMutex();
        acceptCond = createCondition();
    }

    void onAccept(int fd,String ip,int port,ByteArray pack) {
      AutoLock ll(acceptMutex);
      printf("on accept pack is %s,size is %d \n",pack->toString()->toChars(),pack->size());
        acceptStr = pack->toString();
        acceptCond->notify();
    }

    void onDisconnect(int fd){
      printf("onDisconnect \n");
      disconnectFd = fd;
    }

    void onConnect(int fd,String ip,int port) {
      AutoLock ll(mutex);
      printf("onConnect,ip is %s,port is %d,fd is %d \n",ip->toChars(),port,fd);
      //AutoLock ll(mutex);
      clientfd = fd;
      cond->notify();
    }

    void onConnect(int fd,String domain) {
      //Do Nothing
    }

    int getClientFd() {
        if(clientfd != 0) {
          return clientfd;
        }

        AutoLock ll(mutex);
        cond->wait(mutex);
        return clientfd;
    }

    String getAcceptString() {
        if(acceptStr != nullptr) {
          return  acceptStr;
        }

        AutoLock ll(acceptMutex);
        acceptCond->wait(acceptMutex);

        return acceptStr;
    }

    int getDisconnectSocket() {
        return disconnectFd;
    }

private:
    int clientfd;
    Mutex mutex;
    Condition cond;

    Mutex acceptMutex;
    Condition acceptCond;

    int disconnectFd;

    String acceptStr;
};

DECLARE_CLASS(DelayReleaser) IMPLEMENTS(Thread) {

public:
    _DelayReleaser(AsyncTcpClient c) {
        client = c;
    }

    void run() {
      sleep(5);
      client->release();
    }

private:
    AsyncTcpClient client;
};


DECLARE_CLASS(DelaySender) IMPLEMENTS(Thread) {
public:
    _DelaySender() {
        mFd = 0;
    }

    ~_DelaySender() {
        printf("DelaySender release \n");
    }

    void sendData(int fd,ByteArray data) {
        mFd = fd;
        mData = data;
    }

    void run() {
        //while(1) {
        //  printf("delaysender trace1 \n");
        //  if(mFd != 0 && mData != nullptr) {
            printf("delaysender trace2 \n");
            sleep(5);
              st(NetUtils)::sendTcpPacket(mFd,mData);
        //      mFd = 0;
        //      mData = nullptr;
        //  } else {
        //    printf("delaysender trace3 \n");
        //      sleep(5);
        //  }
      //  }
    }

    void onInterrupt() {
      printf("delaysender onInterrupt \n");
    }

private:
    int mFd;
    ByteArray mData;    
};

//client listener
DECLARE_CLASS(ClientListener) IMPLEMENTS(SocketListener) {

public:
  _ClientListener() {
      connectMutex = createMutex();
      connectCond = createCondition();

      acceptMutex = createMutex();
      acceptCond = createCondition();
  }

  void onAccept(int fd,String ip,int port,ByteArray pack) {
      printf("cient accept1 \n");
      AutoLock ll(acceptMutex);
      acceptString = pack->toString();
      acceptCond->notify();
      printf("cient accept2 \n");
  }

  void onDisconnect(int fd) {
      AutoLock ll(connectMutex);
      mIsConnect = false;
      connectCond->notify();
  }

  void onConnect(int fd,String ip,int port) {
      AutoLock ll(connectMutex);
      mIsConnect = true;
      connectCond->notify();
  }

  void onConnect(int fd,String domain) {

  }

  String getAcceptString() {
      if(acceptString != nullptr) {
          return acceptString;
      }
      printf("cient get accept1 \n");
      AutoLock ll(acceptMutex);
      acceptCond->wait(acceptMutex);
      printf("cient get accept2 \n");
      return acceptString;
  }

  bool isConnect() {
      return mIsConnect;
  }

private:
    Mutex connectMutex;
    bool mIsConnect;
    int fd;
    Condition connectCond;

    Mutex acceptMutex;
    String acceptString;
    Condition acceptCond;

};


int main() {

  printf("--- AsyncTcpClient Test --- \n");
  ServerListener listener = createServerListener();
  TcpServer server = createTcpServer(1111,listener);
  server->start();
  //void start();
  while(1) {
    {
        AsyncTcpClient client = createAsyncTcpClient(1111,createClientListener());
        client->start();
    }

    sleep(1);
     
    printf("---[AsyncTcpClient Test {start()} case1] [Success]--- \n");
    break;
  }

  //void release();
  while(1) {
    AsyncTcpClient client = createAsyncTcpClient(1111,createClientListener());
    client->start();
    sleep(1);
    client->release();
    client = nullptr;

    printf("---[AsyncTcpClient Test {release()} case1] [Success]--- \n");
    break;
  }

  //void wait();
  while(1) {
    AsyncTcpClient client = createAsyncTcpClient(1111,createClientListener());
    client->start();
    sleep(1);
    DelayReleaser releaser = createDelayReleaser(client);
    releaser->start();
    client->wait();
    printf("---[AsyncTcpClient Test {wait()} case1] [Success]--- \n");
    break;
  }

  //int send(ByteArray);
  while(1) {
    AsyncTcpClient client = createAsyncTcpClient(1111,createClientListener());
    client->start();

    String str = createString("nihao");
    client->send(createByteArray(str));
    sleep(1);

    String accept = listener->getAcceptString();
    if(accept == nullptr || !accept->equals(str)) {
      printf("---[AsyncTcpClient Test {send(ByteArray)} case1] [Fail]--- \n");
      break;
    }

    printf("---[AsyncTcpClient Test {send(ByteArray)} case1] [Success]--- \n");
    break;
  }

  //int acceptString
  while(1) {
    ClientListener clientLis = createClientListener();
    AsyncTcpClient client = createAsyncTcpClient(1111,clientLis);
    client->start();

    DelaySender sender = createDelaySender();
    int fd = listener->getClientFd();
    String str = createString("helloworld");
    sender->sendData(fd,createByteArray(str));
    sender->start();

    String accept = clientLis->getAcceptString();
    if(accept == nullptr || !accept->equals(str)) {
      printf("---[AsyncTcpClient Test {acceptString()} case1] [Fail]--- \n");
      break;
    }

    printf("---[AsyncTcpClient Test {acceptString()} case2] [Success]--- \n");
    break;
  }

  server->release();
  sleep(5);  

}
