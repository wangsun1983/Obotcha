#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"
#include "HttpServer.hpp"
#include "HttpPacketWriter.hpp"
#include "HttpCookie.hpp"
#include "HttpResponse.hpp"
#include "HttpStatus.hpp"
#include "HttpServerBuilder.hpp"
#include "Inet4Address.hpp"
#include "CountDownLatch.hpp"

using namespace obotcha;

CountDownLatch latch = createCountDownLatch(1);

DECLARE_CLASS(MyHttpListener) IMPLEMENTS(HttpListener) {


void onHttpMessage(int event,HttpLinker client,HttpResponseWriter w,HttpPacket msg){
    switch(event) {
        case HttpEvent::Connect: {
            //connectCount->incrementAndGet();
        }
        break;

        case HttpEvent::Message: {
            //messageCount->incrementAndGet();
            HttpEntity entity = msg->getEntity();
          
            HttpUrlEncodedValue v = createHttpUrlEncodedValue(entity->getContent()->toString());
            
            //printf("key1 is %s,vaue1 is %s \n",keyvalue1->getKey()->toChars(),keyvalue1->getValue()->toChars());
            if(!v->get("tag1")->equals("value1")) {
                printf("---TestHttpServer Request Encode test1 [FAILED]---\n");
            }

            if(!v->get("tag2")->equals("value2")) {
                printf("---TestHttpServer Request Encode test1 [FAILED]---\n");
            }
            
            HttpResponse response = createHttpResponse();
            response->getHeader()->setResponseStatus(st(HttpStatus)::Ok);
            w->write(response);
          
            latch->countDown();
        }
        break;

        case HttpEvent::Disconnect:{
            //disConnectCount->incrementAndGet();
        }
        break;
    }
}

};

int main() {
  MyHttpListener listener = createMyHttpListener();
  HttpServer server = createHttpServerBuilder()
                    ->setAddress(createInet4Address(1124))
                    ->setListener(listener)
                    ->build();
  server->start();
  latch->await();

  printf("---TestHttpServer Request Encode test100 [OK]---\n");
}
