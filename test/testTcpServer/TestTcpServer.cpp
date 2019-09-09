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

int clientfd;
String response = nullptr;
Mutex mutex = createMutex("tcp test");
Condition mCond = createCondition();

DECLARE_SIMPLE_CLASS(ServerListener) IMPLEMENTS(SocketListener) {
public:
    void onAccept(int fd,String ip,int port,ByteArray pack) {
      printf("on accept pack is %s \n",pack->toValue());
      mutex->lock();
      response = createString(pack->toValue());
      mCond->notify();
      mutex->unlock();
      //ByteArray arr = createByteArray(createString("nihao from server"));
      //st(NetUtils)::sendTcpPacket(fd,arr);
    }

    void onDisconnect(int fd){
      printf("onDisconnect \n");
    }

    void onConnect(int fd,String ip,int port) {
      printf("onConnect,ip is %s,port is %d,fd is %d \n",ip->toChars(),port,fd);
      mutex->lock();
      clientfd = fd;
      mCond->notify();
      mutex->unlock();
    }

    void onConnect(int fd,String domain) {}
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

//void testTcpServer() {
//  TcpServer server = createTcpServer(1111,createServerListener());
  //CloseThread t = createCloseThread(server);
  //t->start();

//  server->start();
//}

int main() {
  printf("---[TcpServer Test Start]--- \n");
  
#if 0
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
#endif

  //int send(int fd,ByteArray data);
  while(1) {
      //connect TcpTestServer;
      system("./../tools/TcpTestTools/TcpClientSender/bin/tcpclientsender &");
      sleep(1);
      printf("start test \n");
      ServerListener listener = createServerListener();
      TcpServer server = createTcpServer(1111,listener);
      server->start();
      File f = createFile("sendcontent.txt");
      if(!f->exists()) {
        printf("f is not exists \n");
      }

      FileOutputStream stream = createFileOutputStream(f);
      stream->open(Trunc);
      ByteArray sendcontent = createByteArray(1);
      stream->write(sendcontent); //send /0 to server to wait message from server;
      stream->flush();
      mutex->lock();
      if(response == nullptr) {
          mCond->wait(mutex);  
      }
      mutex->unlock();

      String str = createString("hello");
      if(clientfd == 0) {
        printf("clientfd is 0 \n");
      }

      server->send(clientfd,createByteArray(str));
      sleep(1);
      
      mutex->lock();
      if(response == nullptr) {
          mCond->wait(mutex);  
      }
      mutex->unlock();

      if(response == nullptr || !response->equals(str)) {
          printf("---[TcpServer Test {send()} case1] [FAIL]--- \n");
          break;
      }

      //close testserver
      sendcontent = createByteArray(1);
      stream->write(sendcontent); //send /0 to server to wait message from server;
      stream->flush();
      stream->close();

      printf("---[TcpServer Test {send()} case2] [Success]--- \n");
      break;

  }

  /*
  _TcpServer(int port,SocketListener l);

    _TcpServer(String ip,int port,SocketListener l);


    void release();

    int send(int fd,ByteArray data);

    void removeClientFd(int fd);

    void addClientFd(int fd);

    ~_TcpServer();
  */
}
