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

using namespace obotcha;

AtomicInteger connectCount = createAtomicInteger(0);
AtomicInteger disConnectCount = createAtomicInteger(0);
AtomicInteger messageCount = createAtomicInteger(0);

CountDownLatch latch = createCountDownLatch(1024);

DECLARE_CLASS(MyHttpListener) IMPLEMENTS(HttpListener) {


void onHttpMessage(int event,HttpLinker client,sp<_HttpResponseWriter> w,HttpPacket msg){
    switch(event) {
        case HttpEvent::Connect: {
            connectCount->incrementAndGet();
        }
        break;

        case HttpEvent::Message: {
            messageCount->incrementAndGet();

            HttpResponse response = createHttpResponse();
            response->getHeader()->setResponseStatus(st(HttpStatus)::Ok);

            String body = createString("<h1>Response from Gagira</h1>");
            HttpEntity entity = createHttpEntity();
            entity->setContent(createByteArray(body));
            response->setEntity(entity);

            w->write(response);
        }
        break;

        case HttpEvent::Disconnect:{
            disConnectCount->incrementAndGet();
            latch->countDown();
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
  latch->await();
  server->close();
  if(connectCount->get() != 1024) {
    printf("---TestHttpServer Simple Sync test1 [FAILED]---,connectCount is %d \n",connectCount->get());
  }

  if(disConnectCount->get() != 1024) {
    printf("---TestHttpServer Simple Sync test2 [FAILED]---,disConnectCount is %d \n",disConnectCount->get());
  }

  if(messageCount->get() != 1024) {
    printf("---TestHttpServer Simple Sync test1 [FAILED]---,messageCount is %d \n",messageCount->get());
  }
  
  printf("---TestHttpServer Simple Sync test100 [OK]---\n");
}
