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
#include "Md.hpp"


using namespace obotcha;


CountDownLatch latch = createCountDownLatch(1024);

DECLARE_CLASS(MyHttpListener) IMPLEMENTS(HttpListener) {


void onHttpMessage(int event,HttpLinker client,sp<_HttpResponseWriter> w,HttpPacket msg){
    switch(event) {
        case HttpEvent::Connect: {
            //connectCount->incrementAndGet();
        }
        break;

        case HttpEvent::Message: {
            //messageCount->incrementAndGet();
            HttpResponse response = createHttpResponse();
            response->getHeader()->setResponseStatus(st(HttpStatus)::Ok);
            File file = createFile("pic.png");
            response->setFile(file);
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
                    ->setAddress(createInet4Address(1123))
                    ->setListener(listener)
                    ->build();
  server->start();
  latch->await();

  Md md5 = createMd();
  String v1 = md5->encrypt(createFile("pic.png"));

  for(int i = 0;i<1024;i++) {
    File f = createFile(createString(i)->append(".png"));
    if(!f->exists()) {
        printf("---TestHttpServer testChunckFileServer test1 [FAILED]---\n");
        break;
    }

    
    String v2 = md5->encrypt(f);
    f->removeAll();
    
    if(!v1->equals(v2)) {
        printf("---TestHttpServer testChunckFileServer test2 [FAILED]---,index = %d\n",i);
        break;
    }
  }

  printf("---TestHttpServer testChunckFileServer test100 [OK]--- \n");
  
}
