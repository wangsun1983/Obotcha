#include "TcpServer.hpp"
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

using namespace obotcha;

String testTcpServerSendResult();
String testTcpServerAcceptResult();

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
      printf("on accept pack is %s,size is %d \n",pack->toString()->toChars(),pack->size());
        acceptStr = pack->toString();
        acceptCond->notify();
    }

    void onDisconnect(int fd){
      printf("onDisconnect \n");
    }

    void onConnect(int fd,String ip,int port) {
      printf("onConnect,ip is %s,port is %d,fd is %d \n",ip->toChars(),port,fd);
      //AutoMutex ll(mutex);
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

        AutoMutex ll(mutex);
        cond->wait(mutex);
        return clientfd;
    }

    String getAcceptString() {
        if(acceptStr != nullptr) {
          return  acceptStr;
        }

        AutoMutex ll(acceptMutex);
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

DECLARE_SIMPLE_CLASS(TestSendClient) IMPLEMENTS(Thread) {
public:
    _TestSendClient() {
      mutex = createMutex();
      mCond = createCondition();
    }

    void run() {
        resultStr = testTcpServerSendResult();
        mCond->notify();
    }

    String getResult() {
        if(resultStr != nullptr) {
          return  resultStr;
        }
        AutoMutex ll(mutex);
        mCond->wait(mutex);
        return resultStr;
    }

private:
    String resultStr;
    Mutex mutex;
    Condition mCond;

};


DECLARE_SIMPLE_CLASS(CloseThread) EXTENDS(Thread) {
public:
    _CloseThread(TcpServer c) {
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
    TcpServer server;    
};

int main() {
  printf("---[TcpServer Test Start]--- \n");

  //_TcpServer(int port,SocketListener l);
  while(1) {
      ServerListener listener = createServerListener();
      TcpServer server = createTcpServer(1111,listener);
      if(server == nullptr) {
          printf("---[TcpServer Test {construct()} case1] [FAIL]--- \n");
          break;
      }

      try{
        server = createTcpServer(-1,nullptr);
        printf("---[TcpServer Test {construct()} case2] [FAIL]--- \n");
        break;
      } catch(InitializeException e) {}

      server->release();
      printf("---[TcpServer Test {construct()} case2] [Success]--- \n");
      break;
  }

  //_TcpServer(String ip,int port,SocketListener l);
  while(1) {
      ServerListener listener = createServerListener();
      String ip = createString("192.168.0.111");

      TcpServer server = createTcpServer(ip,111,listener);
      if(server == nullptr) {
          printf("---[TcpServer Test {construct(int,int,SocketListener)} case1] [FAIL]--- \n");
          break;
      }

      try{
        server = createTcpServer(ip,-123,nullptr);
        printf("---[TcpServer Test {construct(int,int,SocketListener)} case2] [FAIL]--- \n");
        break;
      } catch(InitializeException e) {}
      server->release();
      printf("---[TcpServer Test {construct(int,int,SocketListener)} case2] [Success]--- \n");
      break;

  }


  //int start()/release();
  while(1) {
      String ip = createString("12.22.21.2");
      ServerListener listener = createServerListener();
      TcpServer server = createTcpServer(1111,listener);
      if(server->start() != 0) {
          printf("---[TcpServer Test {start()} case1] [FAIL]--- \n");
          break;
      }
      server->release();

      server = createTcpServer(ip,1,listener);
      if(server->start() == 0) {
          printf("---[TcpServer Test {start()} case2] [FAIL]--- \n");
          break;
      }
      server->release();

      printf("---[TcpServer Test {start()} case3] [Success]--- \n");
      break;
  }


  //int send(int fd,ByteArray data);
  while(1) {
      ServerListener listener = createServerListener();
      TcpServer server = createTcpServer(1111,listener);
      server->start();
      TestSendClient client = createTestSendClient();
      client->start();
      
      String str = createString("hello");
      int fd = listener->getClientFd();
      server->send(fd,createByteArray(str));

      String result = client->getResult();
      printf("getResult is %s \n",result->toChars());
      if(!result->equals(str)) {
          printf("---[TcpServer Test {send()} case1] [FAIL]--- \n");
          break;
      }

      printf("---[TcpServer Test {send()} case1] [Success]--- \n");
      break;

  }

  //Accept Callback
  while(1) {
      ServerListener listener = createServerListener();
      TcpServer server = createTcpServer(1111,listener);
      server->start();
      String str = testTcpServerAcceptResult();

      String acceptString = listener->getAcceptString();
      if(acceptString == nullptr || !acceptString->equals(str)) {
        printf("---[TcpServer Test {onAccept()} case1] [FAIL]--- \n");
        break;
      }

      printf("---[TcpServer Test {onAccept()} case1] [Success]--- \n");
      break;  
  }

  //release()
  while(1) {
      ServerListener listener = createServerListener();
      TcpServer server = createTcpServer(1111,listener);
      server->start();
      sleep(1);
      server->release();
      sleep(1);
      if(server->getStatus() != ServerThreadExited) {
          printf("---[TcpServer Test {release()} case1] [FAIL]--- \n");
          break;
      }
      
      printf("---[TcpServer Test {release()} case2] [Success]--- \n");
      break;
  }

  sleep(10);

}
