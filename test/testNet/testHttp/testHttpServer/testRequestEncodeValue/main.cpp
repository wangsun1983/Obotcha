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

CountDownLatch latch = createCountDownLatch(1);

DECLARE_CLASS(MyHttpListener) IMPLEMENTS(HttpListener) {


void onHttpMessage(int event,HttpLinker client,sp<_HttpResponseWriter> w,HttpPacket msg){
    switch(event) {
        case HttpEvent::Connect: {
            //connectCount->incrementAndGet();
        }
        break;

        case HttpEvent::Message: {
            //messageCount->incrementAndGet();
            HttpEntity entity = msg->getEntity();
            auto lists = entity->getEncodedKeyValues();
            
            auto keyvalue1 = lists->get(0);
            //printf("key1 is %s,vaue1 is %s \n",keyvalue1->getKey()->toChars(),keyvalue1->getValue()->toChars());
            if(!keyvalue1->getKey()->equals("tag1")) {
                printf("---TestHttpServer Request Encode test1 [FAILED]---\n");
            }

            if(!keyvalue1->getValue()->equals("value1")) {
                printf("---TestHttpServer Request Encode test2 [FAILED]---\n");
            }

            auto keyvalue2 = lists->get(1);
            //printf("key2 is %s,vaue2 is %s \n",keyvalue2->getKey()->toChars(),keyvalue2->getValue()->toChars());
            if(!keyvalue2->getKey()->equals("tag2")) {
                printf("---TestHttpServer Request Encode test3 [FAILED]---\n");
            }

            if(!keyvalue2->getValue()->equals("value2")) {
                printf("---TestHttpServer Request Encode test4 [FAILED]---\n");
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
