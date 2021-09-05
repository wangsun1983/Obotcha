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

CountDownLatch connectlatch = createCountDownLatch(1024*32*16);
CountDownLatch disconnetlatch = createCountDownLatch(1024*32*16);

DECLARE_CLASS(MyHandler) IMPLEMENTS(Handler) {
public:
  void handleMessage(Message msg) {
    printf("connect is %d,disconnect is %d \n",connectlatch->getCount(),disconnetlatch->getCount());
    this->sendEmptyMessageDelayed(0,10*1024);
  }
};

DECLARE_CLASS(MyHttpListener) IMPLEMENTS(HttpListener) {
  void onHttpMessage(int event,HttpLinker client,sp<_HttpResponseWriter> w,HttpPacket msg){
      switch(event) {
          case HttpEvent::Connect: {
              connectlatch->countDown();
          }
          break;

          case HttpEvent::Message: {
              HttpResponse response = createHttpResponse();
              response->getHeader()->setResponseStatus(st(HttpStatus)::Ok);
              w->write(response);
          }
          break;

          case HttpEvent::Disconnect:{
              disconnetlatch->countDown();
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
  connectlatch->await();
  disconnetlatch->await();
  server->close();
  
  printf("---TestHttpServer MultiClientConnect test100 [OK]---\n");
}
