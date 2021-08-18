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

using namespace obotcha;

AtomicInteger connectCount = createAtomicInteger(0);
AtomicInteger disConnectCount = createAtomicInteger(0);
AtomicInteger messageCount = createAtomicInteger(0);

DECLARE_CLASS(MyHttpListener) IMPLEMENTS(HttpListener) {


void onHttpMessage(int event,HttpLinker client,sp<_HttpResponseWriter> w,HttpPacket msg){
    switch(event) {
        case HttpEvent::Connect: {
            printf("on connect \n");
            connectCount->incrementAndGet();
        }
        break;

        case HttpEvent::Message: {
            printf("on message \n");
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
            printf("on disconnect \n");
            disConnectCount->incrementAndGet();
        }
        break;
    }
}

};

int main() {
  MyHttpListener listener = createMyHttpListener();
  HttpServer server = createHttpServerBuilder()
                    ->setAddress(createInet4Address("192.168.1.9",1256))
                    ->setListener(listener)
                    ->build();
  server->start();
  while(1) {
  sleep(30);
  }
  server->close();
  printf("connectCount is %d,disConnectCount is %d,messageCount is %d \n",connectCount->get(),disConnectCount->get(),messageCount->get());
  
}
