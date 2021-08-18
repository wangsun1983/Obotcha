#include "TcpServer.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Thread.hpp"
#include "NetUtils.hpp"
#include "HttpResponse.hpp"

using namespace obotcha;

DECLARE_CLASS(ServerListener) IMPLEMENTS(SocketListener) {
public:
    void onAccept(int fd,String ip,int port,ByteArray pack) {
      printf("on accept pack is %s \n",pack->toValue());

//#if 0
      HttpResponse response = createHttpResponse();
      response->setHeaderValue(Http_Header_Status,"200");

      String body = createString("<h1>Response from Gagira</h1>");
      body = body->append("<h2>Response from Gagira</h2> \r\n");
      body = body->append("<h3>Response from Gagira</h3> \r\n");

      response->setHeaderValue(Http_Header_Content_Length,createString(body->size()));
      response->setBody(createByteArray(body));
      String resp = response->generateResponse();
      ByteArray arr = createByteArray(resp);
      printf("response is %s \n",resp->toChars());
      st(NetUtils)::sendTcpPacket(fd,arr);
 //#endif

      //ByteArray arr = createByteArray(createString("nihao from server \n" ));
      //int rest = st(NetUtils)::sendTcpPacket(fd,arr);
      //printf("on accept end,rest is %d \n",rest);

    }

    void onDisconnect(int fd){
      printf("onDisconnect \n");
    }

    void onConnect(int fd,String ip,int port) {
      printf("onConnect,ip is %s,port is %d,fd is %d \n",ip->toChars(),port,fd);
      //ByteArray arr = createByteArray(createString("nihao from server"));
      //st(NetUtils)::sendTcpPacket(fd,arr);

      printf("onConnect end \n");
    }

    void onConnect(int fd,String domain) {}
};

DECLARE_CLASS(CloseThread) EXTENDS(Thread) {
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
  ServerListener listener = createServerListener();
  TcpServer server = createTcpServer(1111,listener);
  //CloseThread t = createCloseThread(server);
  //t->start();

  server->start();
  //testTcpServer();
  while(1) {}
  printf("end main!!!! \n");
}
