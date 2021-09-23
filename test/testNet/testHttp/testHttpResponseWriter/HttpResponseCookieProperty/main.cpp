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
#include "Calendar.hpp"

using namespace obotcha;

CountDownLatch latch = createCountDownLatch(1);
int count = 0;


DECLARE_CLASS(MyHttpListener) IMPLEMENTS(HttpListener) {
  void onHttpMessage(int event,HttpLinker client,sp<_HttpResponseWriter> w,HttpPacket msg){
      switch(event) {
          case HttpEvent::Connect: {
              //connectlatch->countDown();
          }
          break;

          case HttpEvent::Message: {
              if(count == 0) {
                //first message to send response with cookie
                HttpResponse response = createHttpResponse();
                HttpCookie cookie1 = createHttpCookie("test2_tag1","test2_value1");
                cookie1->setPropertySecure(true);
                cookie1->setPropertyHttpOnly(true);
                cookie1->setPropertyPath("/path123");
                //cookie1->setPropertyDomain("domain123");
                cookie1->setPropertyExpires(createHttpDate(createCalendar()->getDateTime()));
                //cookie1->setPropertyMaxAge(100000);


                HttpCookie cookie2 = createHttpCookie("test2_tag2","test2_value2");
                response->getHeader()->addCookie(cookie1);
                response->getHeader()->addCookie(cookie2);
                response->getHeader()->setResponseStatus(st(HttpStatus)::Ok);
                w->write(response);
                //count++;
              } else if(count == 1) {
                //TODO
                HttpEntity entity = msg->getEntity();
                auto lists = entity->getEncodedKeyValues();
                auto keyvalue1 = lists->get(0);
                
                //printf("key1 is %s,vaue1 is %s \n",keyvalue1->getKey()->toChars(),keyvalue1->getValue()->toChars());
                if(!keyvalue1->getKey()->equals("test2_tag1")) {
                    printf("---TestHttpResponseWriter Request Encode test1 [FAILED]---\n");
                }

                if(!keyvalue1->getValue()->equals("test2_value1")) {
                    printf("---TestHttpResponseWriter Request Encode test2 [FAILED]---\n");
                }

                auto keyvalue2 = lists->get(1);
                //printf("key2 is %s,vaue2 is %s \n",keyvalue2->getKey()->toChars(),keyvalue2->getValue()->toChars());
                if(!keyvalue2->getKey()->equals("test2_tag2")) {
                    printf("---TestHttpResponseWriter Request Encode test3 [FAILED]---\n");
                }

                if(!keyvalue2->getValue()->equals("test2_value2")) {
                    printf("---TestHttpResponseWriter Request Encode test4 [FAILED]---\n");
                }

                HttpResponse response = createHttpResponse();
                response->getHeader()->setResponseStatus(st(HttpStatus)::Ok);
                w->write(response);
                //count = 0;
                latch->countDown();
              }
              break;
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
                    ->setAddress(createInet4Address(1256))
                    ->setListener(listener)
                    ->build();
  server->start();
  latch->await();
  server->close();
  
  printf("---TestHttpResponseWriter cookie test100 [OK]---\n");
}
