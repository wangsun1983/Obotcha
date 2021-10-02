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
#include "TimeZone.hpp"

using namespace obotcha;

CountDownLatch latch = createCountDownLatch(1);
int count = 0;

long setExpires = 0;

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
                cookie1->setPropertyPath("path123");
                //cookie1->setPropertyDomain("domain123");
                Calendar c = createCalendar();//->getDateTime()
                //c->add(st(Calendar)::DayOfMonth,1);
                printf("time zone is %d \n",st(TimeZone)::getZone());
                setExpires = (c->toTimeMillis())/1000;
                printf("setExpires is %ld \n",setExpires);

                //cookie1->setPropertyExpires(createHttpDate(c->getGmtDateTime()));
                cookie1->setPropertyMaxAge(1);


                //HttpCookie cookie2 = createHttpCookie("test2_tag2","test2_value2");
                response->getHeader()->addCookie(cookie1);
                //response->getHeader()->addCookie(cookie2);
                response->getHeader()->setResponseStatus(st(HttpStatus)::Ok);
                w->write(response);
                count++;
              } else if(count == 1) {
                //TODO
                HttpEntity entity = msg->getEntity();
                auto lists = entity->getEncodedKeyValues();
                if(lists != nullptr && lists->size() != 0) {
                  printf("---TestHttpResponseWriter Cookie Property MaxAges expire test1 [FAILED]---\n");
                }
                

                HttpResponse response = createHttpResponse();
                response->getHeader()->setResponseStatus(st(HttpStatus)::Ok);
                w->write(response);
                //count = 0;
                latch->countDown();
                count = 0;
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
  sleep(1);
  
  printf("---TestHttpResponseWriter Cookie Property MaxAges expire test100 [OK]---\n");
}
