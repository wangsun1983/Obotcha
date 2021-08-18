#include "LocalSocketServer.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Thread.hpp"
#include "NetUtils.hpp"
#include "InitializeException.hpp"
#include "FileOutputStream.hpp"
#include "File.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "System.hpp"
#include "LocalSocketServer.hpp"

using namespace obotcha;

String testLocalSocketServerSendResult();
String testLocalSocketServerAcceptResult();

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
      printf("on accept pack is %s,size is %d \n",pack->toString()->toChars(),pack->size());
        acceptStr = pack->toString();
        acceptCond->notify();
    }

    void onDisconnect(int fd){
      printf("onDisconnect \n");
    }

    void onConnect(int fd,String ip,int port) {
      printf("onConnect,ip is %s,port is %d,fd is %d \n",ip->toChars(),port,fd);
      //AutoLock ll(mutex);
      clientfd = fd;
      cond->notify();
    }

    void onConnect(int fd,String domain) {
      //Do Nothing
      printf("onConnect2222,,domain is %s \n",domain->toChars());
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

private:
    int clientfd;
    Mutex mutex;
    Condition cond;

    Mutex acceptMutex;
    Condition acceptCond;

    String acceptStr;
};

DECLARE_CLASS(TestSendClient) IMPLEMENTS(Thread) {
public:
    _TestSendClient() {
      mutex = createMutex();
      mCond = createCondition();
    }

    void run() {
        resultStr = testLocalSocketServerSendResult();
        mCond->notify();
    }

    String getResult() {
        if(resultStr != nullptr) {
          return  resultStr;
        }
        AutoLock ll(mutex);
        mCond->wait(mutex);
        return resultStr;
    }

private:
    String resultStr;
    Mutex mutex;
    Condition mCond;

};


DECLARE_CLASS(CloseThread) EXTENDS(Thread) {
public:
    _CloseThread(LocalSocketServer c) {
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
    LocalSocketServer server;    
};

int main() {
  printf("---[LocalSocketServer Test Start]--- \n");

  //_LocalSocketServer(int port,SocketListener l);
  while(1) {
      ServerListener listener = createServerListener();
      LocalSocketServer server = createLocalSocketServer(createString("/tmp/abcd"),listener);
      if(server == nullptr) {
          printf("---[LocalSocketServer Test {construct()} case1] [FAIL]--- \n");
          break;
      }

      server->release();
      printf("---[LocalSocketServer Test {construct()} case2] [Success]--- \n");
      break;
  }


  //int send(int fd,ByteArray data);
  while(1) {
      ServerListener listener = createServerListener();
      LocalSocketServer server = createLocalSocketServer(createString("/tmp/abcd"),listener);
      server->start();
      TestSendClient client = createTestSendClient();
      client->start();
      
      String str = createString("hello");
      int fd = listener->getClientFd();
      server->send(fd,createByteArray(str));

      String result = client->getResult();
      printf("getResult is %s \n",result->toChars());
      if(!result->equals(str)) {
          printf("---[LocalSocketServer Test {send()} case1] [FAIL]--- \n");
          break;
      }

      printf("---[LocalSocketServer Test {send()} case1] [Success]--- \n");
      break;

  }

  //Accept Callback
  while(1) {
      ServerListener listener = createServerListener();
      LocalSocketServer server = createLocalSocketServer(createString("/tmp/abcd"),listener);
      server->start();
      String str = testLocalSocketServerAcceptResult();

      String acceptString = listener->getAcceptString();
      if(acceptString == nullptr || !acceptString->equals(str)) {
        printf("---[LocalSocketServer Test {onAccept()} case1] [FAIL]--- \n");
        break;
      }

      printf("---[LocalSocketServer Test {onAccept()} case1] [Success]--- \n");
      break;  
  }

  //release()
  while(1) {
      ServerListener listener = createServerListener();
      LocalSocketServer server = createLocalSocketServer(createString("/tmp/abcd"),listener);
      server->start();
      sleep(1);
      server->release();
      sleep(1);
      if(server->getStatus() != LocalServerThreadExited) {
          printf("---[LocalSocketServer Test {release()} case1] [FAIL]--- \n");
          break;
      }
      
      printf("---[LocalSocketServer Test {release()} case2] [Success]--- \n");
      break;
  }


  sleep(10);

}
