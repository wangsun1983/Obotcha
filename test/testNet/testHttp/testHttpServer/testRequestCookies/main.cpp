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
            HttpHeader header = msg->getHeader();
            auto cookies = header->getCookies();

            auto v1 = cookies->get(0);
            if(!v1->getName()->equals("tag1")) {
                printf("---TestHttpServer Request Cookie test1 [FAILED]---\n");
            }

            if(!v1->getValue()->equals("value1")) {
                printf("---TestHttpServer Request Cookie test2 [FAILED]---\n");
            }

            auto v2 = cookies->get(1);
            if(!v2->getName()->equals("tag2")) {
                printf("---TestHttpServer Request Cookie test3 [FAILED]---\n");
            }

            if(!v2->getValue()->equals("value2")) {
                printf("---TestHttpServer Request Cookie test4 [FAILED]---\n");
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

  printf("---TestHttpServer Request Cookie test100[OK]---\n");
}
