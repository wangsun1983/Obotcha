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



DECLARE_SIMPLE_CLASS(MyHttpListener) IMPLEMENTS(HttpListener) {


void onHttpMessage(int event,HttpLinker client,sp<_HttpResponseWriter> w,HttpPacket msg){
    switch(event) {
        case HttpEvent::Connect: {
            //connectCount->incrementAndGet();
        }
        break;

        case HttpEvent::Message: {
            //messageCount->incrementAndGet();
            printf("i accept message \n");

            HttpResponse response = createHttpResponse();
            response->getHeader()->setResponseStatus(st(HttpStatus)::Ok);
            HttpEntity entity = createHttpEntity();
            KeyValuePair<String,String> key1 = createKeyValuePair<String,String>(createString("key1"),createString("val1"));
            KeyValuePair<String,String> key2 = createKeyValuePair<String,String>(createString("key2"),createString("val2"));
            entity->getEncodedKeyValues()->add(key1);
            entity->getEncodedKeyValues()->add(key2);
            response->setEntity(entity);
            w->write(response);
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
                    ->setAddress(createInet4Address("192.168.1.9",1124))
                    ->setListener(listener)
                    ->build();
  server->start();
  while(1) {
    sleep(1);
  }
  
}