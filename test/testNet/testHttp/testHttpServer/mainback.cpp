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


void onHttpMessage(int event,sp<_HttpClientInfo> client,sp<_HttpResponseWriter> w,HttpPacket msg){
    switch(event) {
        case Event::Message:
        connectCount->incrementAndGet();
        break;

        case Event::Connect:
        messageCount->incrementAndGet();

        HttpResponse response = createHttpResponse();
        response->setStatus(st(HttpStatus)::Ok);
        response->setEntity(msg->getEntity())
        w->write(response);
        break;

        case Event::Disconnect:
        disConnectCount->incrementAndGet();
        break;
    }
}

};

int main() {
  MyHttpListener listener = createMyHttpListener();
  HttpServer server = createHttpServerBuilder()
                    ->setAddress(createInet4Address("192.168.1.3",1212))
                    ->setListener(listener)
                    ->build();
  server->start();
  printf("connectCount is %d,disConnectCount is %d,messageCount is %d \n",connectCount->get(),disConnectCount->get(),messageCount->get());
  sleep(100);
}
