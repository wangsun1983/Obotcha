#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"
#include "HttpServer.hpp"
#include "HttpCookie.hpp"
#include "HttpResponse.hpp"
#include "HttpStatus.hpp"
#include "HttpServerBuilder.hpp"
#include "Inet4Address.hpp"
#include "CountDownLatch.hpp"
#include "Handler.hpp"
#include "HttpPacketWriter.hpp"
#include "Enviroment.hpp"

using namespace obotcha;


CountDownLatch connectlatch = createCountDownLatch(1);
int step = 0;

DECLARE_CLASS(MyHttpListener) IMPLEMENTS(HttpListener) {
  void onHttpMessage(int event,HttpLinker client,HttpResponseWriter w,HttpPacket msg){
      switch(event) {
          case HttpEvent::Connect: {
              
          }
          break;

          case HttpEvent::Message: {
              printf("write response connect!!! \n");
              if(step == 0) {
                HttpResponse response = createHttpResponse();
                response->getHeader()->setResponseStatus(st(HttpStatus)::Ok);
                response->getEntity()->setContent(createString("hello this is server")->toByteArray());
                w->write(response);
                step = 1;
              } else {
                String entity = msg->getEntity()->getContent()->toString();
                if(!entity->equals("hello this is server")) {
                  printf("---TestHttpServer SimpleClientContent test1 [FAILED]---,entity is %s\n",entity->toChars());
                }
                connectlatch->countDown();
              }
          }
          break;

          case HttpEvent::Disconnect:{
          }
          break;
      }
  }
};

int main() {
  MyHttpListener listener = createMyHttpListener();
  HttpServer server = createHttpServerBuilder()
                    ->setAddress(createInet4Address(1260))
                    ->setListener(listener)
                    ->build();
  //printf("thread num is %d \n",st(Enviroment)::DefaultgHttpServerThreadsNum);
  server->start();
  connectlatch->await();
  server->close();
  
  printf("---TestHttpServer SimpleClientContent test100 [OK]---\n");
}
