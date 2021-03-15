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
            HttpEntity entity = msg->getEntity();
            ByteArray data = entity->getContent();
            printf("message is %s \n",data->toString()->toChars());
            HttpResponse response = createHttpResponse();
            response->setStatus(st(HttpStatus)::Ok);
            printf("start send response \n");
            HttpEntity e = createHttpEntity();
            e->setContent(createByteArray(createString("value!!!!")));

            response->setEntity(e);
            int len = w->write(response);
            printf("len is %d \n",len);
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
                    ->setAddress(createInet4Address("192.168.1.3",1122))
                    ->setListener(listener)
                    ->build();
  server->start();
  while(1){sleep(30);}
  server->exit();
  printf("connectCount is %d,disConnectCount is %d,messageCount is %d \n",connectCount->get(),disConnectCount->get(),messageCount->get());
  
}
