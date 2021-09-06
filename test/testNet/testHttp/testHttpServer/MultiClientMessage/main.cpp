#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"
#include "HttpServer.hpp"
#include "HttpResponseWriter.hpp"
#include "HttpCookie.hpp"
#include "HttpResponse.hpp"
#include "HttpStatus.hpp"
#include "HttpServerBuilder.hpp"
#include "Inet4Address.hpp"
#include "CountDownLatch.hpp"
#include "Handler.hpp"

using namespace obotcha;

AtomicInteger connectCount = createAtomicInteger(0);
AtomicInteger disConnectCount = createAtomicInteger(0);
AtomicInteger messageCount = createAtomicInteger(0);

CountDownLatch messageLatch = createCountDownLatch(1024*32*128);


DECLARE_CLASS(MyHandler) IMPLEMENTS(Handler) {
public:
  void handleMessage(Message msg) {
    printf("messageLatch is %d \n",messageLatch->getCount());
    this->sendEmptyMessageDelayed(0,10*1024);
  }
};

DECLARE_CLASS(MyHttpListener) IMPLEMENTS(HttpListener) {
  void onHttpMessage(int event,HttpLinker client,sp<_HttpResponseWriter> w,HttpPacket msg){
      switch(event) {
          case HttpEvent::Connect: {
              //connectlatch->countDown();
          }
          break;

          case HttpEvent::Message: {
              auto data = msg->getEntity()->getContent()->toString();
              //printf("get data is %s \n",data->toChars());
              if(data->equals("hello world")) {
                messageLatch->countDown();
              }
              
              HttpResponse response = createHttpResponse();
              response->getHeader()->setResponseStatus(st(HttpStatus)::Ok);
              HttpEntity entity = createHttpEntity();
              ByteArray rdata = createString("sss")->toByteArray();
              entity->setContent(rdata);
              response->setEntity(entity);

              w->write(response);
          }
          break;

          case HttpEvent::Disconnect:{
              //disconnetlatch->countDown();
          }
          break;
      }
  }
};

int main() {
  MyHttpListener listener = createMyHttpListener();
  HttpServer server = createHttpServerBuilder()
                    ->setAddress(createInet4Address(1256))
                    ->setListener(listener)
                    ->build();
  server->start();
  MyHandler h = createMyHandler();
  h->sendEmptyMessageDelayed(0,10*1024);
  messageLatch->await();
  server->close();
  
  printf("---TestHttpServer MultiClientMessage test100 [OK]---\n");
}
