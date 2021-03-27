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

DECLARE_SIMPLE_CLASS(MyHttpListener) IMPLEMENTS(HttpListener) {


void onHttpMessage(int event,sp<_HttpClientInfo> client,sp<_HttpResponseWriter> w,HttpPacket msg){
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
  sleep(30);
  server->exit();
  printf("connectCount is %d,disConnectCount is %d,messageCount is %d \n",connectCount->get(),disConnectCount->get(),messageCount->get());
  
}
