
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "LocalSocketClient.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "LocalSocketServer.hpp"
#include "NetUtils.hpp"
#include "InitializeException.hpp"
#include "LocalSocketServer.hpp"
#include "LocalSocketClient.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(ServerListener) IMPLEMENTS(SocketListener) {
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
      AutoLock ll(mutex);
      printf("onConnect,domain is %s \n",domain->toChars());
      //AutoLock ll(mutex);
      clientfd = fd;
      cond->notify();
    }

    void onTimeout() {

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


DECLARE_SIMPLE_CLASS(DelaySender) IMPLEMENTS(Thread) {
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
        while(1) {
          printf("delaysender trace1 \n");
          if(mFd != 0 && mData != nullptr) {
            printf("delaysender trace2 \n");
              st(NetUtils)::sendTcpPacket(mFd,mData);
              mFd = 0;
              mData = nullptr;
          } else {
            printf("delaysender trace3 \n");
              sleep(5);
          }
        }
    }

    void onInterrupt() {
      printf("delaysender onInterrupt \n");
    }

private:
    int mFd;
    ByteArray mData;    
};



int main() {

  //_LocalSocketClient(int port,int recv_time,int buff_size = 1024);

  //_LocalSocketClient(String ip,int port,int recv_time,int buff_size = 1024);
    

  //int doSend(ByteArray);

  //ByteArray doReceive();

  //int getBuffSize();

  //void release();

  //~_LocalSocketClient();

  //int doConnect();
  printf("--- LocalSocketClient Test --- \n");
  ServerListener listener = createServerListener();
  LocalSocketServer server = createLocalSocketServer("/tmp/abcd",listener);
  server->start();

  while(1) {
      LocalSocketClient client = createLocalSocketClient("/tmp/abcd",3000);
      if(client->doConnect() != -1) {
          printf("---[LocalSocketClient Test {construct()} case1] [FAIL]--- \n");
          break;
      };
      printf("no connect fd is %d \n",client->getSock());

      client = createLocalSocketClient("/tmp/abcd",3000);
      if(client->doConnect() == -1) {
          printf("---[LocalSocketClient Test {construct()} case2] [FAIL]--- \n");
          break;
      };

      printf("---[LocalSocketClient Test {construct()} case3] [Success]--- \n");
      break;
  }

  //int doSend(ByteArray);
  while(1) {
      LocalSocketClient client = createLocalSocketClient("/tmp/abcd",3000);
      printf("doSend connect trace1 \n");
      if(client->doConnect() == -1) {
          printf("---[LocalSocketClient Test {doSend()} case1] [FAIL]--- \n");
          break;
      };
      printf("doSend connect trace2 \n");
      String sendString = createString("nihao from client");
      ByteArray arr = createByteArray(sendString);
      int sendSize = client->doSend(arr);
      printf("send size is %d \n",sendSize);
      if(sendSize != arr->size()) {
          printf("---[LocalSocketClient Test {doSend()} case2] [FAIL]--- \n");
          break;
      }

      printf("doSend connect trace3 \n");

      String str = listener->getAcceptString();
      if(str != nullptr && !str->equals(sendString)) {
          printf("---[LocalSocketClient Test {doSend()} case3] [FAIL]--- \n");
          break;
      }
      printf("doSend connect trace4 \n");

      if(client->doSend(nullptr) != 0) {
          printf("---[LocalSocketClient Test {doSend()} case4] [FAIL]--- \n");
          break;
      }
      printf("doSend connect trace5 \n");

      printf("---[LocalSocketClient Test {doSend()} case5] [Success]--- \n");
      break;
  }

  //ByteArray doReceive();
  while(1) {
      printf("doSend doReceive trace1 \n");
      LocalSocketClient client = createLocalSocketClient("/tmp/abcd",3000);
      client->doConnect();
      sleep(1);

      DelaySender sender = createDelaySender();
      String str = createString("haha,test");
      ByteArray data = createByteArray(str);

      int fd = listener->getClientFd();
      sender->sendData(fd,data);
      sender->start();
      printf("doSend doReceive trace2 \n");

      ByteArray result = client->doReceive();
      printf("result size is %d \n",result->size());
      if(result == nullptr) {
        printf("---[LocalSocketClient Test {doReceive()} case1] [FAIL]--- \n");
        break;
      }

      String rcvString = result->toString();
      printf("rcvString is %s,size is %d \n",rcvString->toChars(),rcvString->size());
      if(!rcvString->equals(str)) {
        printf("---[LocalSocketClient Test {doReceive()} case2] [FAIL]--- \n");
        break;
      }

      sender->quit();
      printf("---[LocalSocketClient Test {doReceive()} case3] [Success]--- \n");
      break;
  }

  //int getBuffSize();
  while(1) {
      LocalSocketClient client = createLocalSocketClient("/tmp/abcd",3000,1);
      if(client->getBuffSize() != 1) {
        printf("---[LocalSocketClient Test {getBuffSize()} case1] [FAIL]--- \n");
        break;
      }

      try {
        client = createLocalSocketClient("/tmp/abcd",3000,-1);
      } catch(InitializeException e) {
        printf("---[LocalSocketClient Test {getBuffSize()} case2] [Success]--- \n");
        break;
      }

      printf("---[LocalSocketClient Test {getBuffSize()} case3] [FAIL]--- \n");
      break;
  }

  //void release();
  while(1) {
    sleep(5);
    LocalSocketClient client = createLocalSocketClient("/tmp/abcd",3000);
    client->doConnect();
    sleep(1);

    int fd = client->getSock();
    if(fd != listener->getDisconnectSocket()) {
        printf("---[LocalSocketClient Test {release()} case1] [FAIL]--- \n");
        break;
    }

    printf("---[LocalSocketClient Test {release()} case2] [Success]--- \n");
    break;
  }


  server->release();
  sleep(5);  
}
