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
            //TODO
        }
        break;

        case HttpEvent::Message: {
            printf("i get a message \n");
            HttpEntity entity = msg->getEntity();
            HttpMultiPart multiPart = entity->getMultiPart();
            if(multiPart != nullptr && multiPart->contents != nullptr) {
              multiPart->contents->foreach([](KeyValuePair<String,String> pair){
                printf("key is %s,value is %s \n",pair->getKey()->toChars(),pair->getValue()->toChars());
                return 1;
              });
            }

            if(multiPart != nullptr && multiPart->files != nullptr) {
                multiPart->files->foreach([](HttpMultiPartFile file){
                  HttpFile f = file->getHttpFile();
                  printf("path is %s \n",f->getAbsolutePath()->toChars());
                  return 1;
                });
            }

            HttpResponse response = createHttpResponse();

            HttpEntity e = createHttpEntity();
            e->setContent(createByteArray(createString("value!!!!")));
            response->setEntity(e);
            int len = w->write(response);
            //printf("len is %d \n",len);
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
                    ->setAddress(createInet4Address(1256))
                    ->setListener(listener)
                    ->build();
  server->start();
  while(1){sleep(30);}
  server->close();
  //printf("connectCount is %d,disConnectCount is %d,messageCount is %d \n",connectCount->get(),disConnectCount->get(),messageCount->get());
  
}
