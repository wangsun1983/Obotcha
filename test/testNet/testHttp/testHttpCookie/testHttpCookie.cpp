#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Aes.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "NumberFormatter.hpp"
#include "Calendar.hpp"
#include "DateTimeFormatter.hpp"
#include "HttpCookie.hpp"
#include "Thread.hpp"
#include "NetUtils.hpp"
#include "HttpResponse.hpp"
#include "TcpServer.hpp"

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

      //wangsl
      HttpCookie cookie = createHttpCookie();
      cookie->setName(createString("name1"));
      cookie->setValue(createString("value1"));
      //cookie->setExpires(1565861065771);
      cookie->setMaxAge(120);
      cookie->setDomain("192.168.43.90");
      cookie->setPath("/");

      HttpCookie cookie2 = createHttpCookie();
      cookie2->setName(createString("name2"));
      cookie2->setValue(createString("value2"));
      //cookie->setExpires(1565861065771);
      cookie2->setMaxAge(120);
      cookie2->setDomain("192.168.43.90");
      cookie2->setPath("/");
      response->addCookie(cookie2);

      //wangsl

      response->setBody(createByteArray(body));
      String resp = response->generateResponse();
      ByteArray arr = createByteArray(resp);
      printf("================================================ \n");
      printf("response is %s \n",resp->toChars());
      printf("================================================ \n");
      st(NetUtils)::sendTcpPacket(fd,arr);
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
