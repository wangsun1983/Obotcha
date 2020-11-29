#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"
#include "HttpV1Server.hpp"
#include "HttpV1ClientInfo.hpp"
#include "HttpV1ResponseWriter.hpp"


using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyHttpListener) IMPLEMENTS(HttpV1Listener) {
public:

    void onMessage(HttpV1ClientInfo client,HttpV1ResponseWriter w,HttpPacket msg) {
        if(msg->getBody()!= nullptr) {
            printf("msg is %s \n",msg->getBody()->toValue());
        }

        HttpMultiPart m = msg->getMultiPart();
        if(m != nullptr) {
            ArrayList<HttpMultiPartData> datas = m->getDatas();
            ListIterator<HttpMultiPartData> itertator = datas->getIterator();
            while(itertator->hasValue()) {
                HttpMultiPartData data = itertator->getValue();
                printf("data->type is %d \n",data->getType());
                switch(data->getType()) {
                    case st(HttpMultiPartData)::PartBlock:{
                        printf("111 data addr is %x",data.get_pointer());
                        HttpMultiPartBlock b = transform_cast<tp(HttpMultiPartBlock)>(data);
                        printf("b addr is %x,data addr is %x",b.get_pointer(),data.get_pointer());
                        if(b->getName() != nullptr) {
                            printf("b name is %s \n",b->getName()->toChars());
                        }

                        if(b->getValue() != nullptr) {
                            printf("b value is %s \n",b->getValue()->toChars());
                        }
                        //printf("b name is %s,value is %s",b->getName()->toChars(),b->getValue()->toChars());
                    }
                        
                        
                    break;

                    case st(HttpMultiPartData)::PartFile:
                    //TODO
                    break;
                }
                itertator->next();
            }
        }
        
        w->setStatus(st(HttpResponse)::Ok);

        String body = createString("<h1>Response from Gagira</h1>");
        //body = body->append("<h2>Response from Gagira</h2> \r\n");
        //body = body->append("<h3>Response from Gagira</h3> \r\n");

        w->writeBody(createByteArray(body));
        //printf("flush!!!! \n");
        w->flush();
        //File f = createFile("testFile");
        //w->write(f);
        //w->flush();
        //response->setHeaderValue(Http_Header_Content_Length,createString(body->size()));
        //w->writeHeader(st(HttpHeader)::ContentLength,createString(body->size()));
        //response->setBody(createByteArray(body));
        //String resp = response->genHttpResponse();
        //int v = client->send(resp);
        //printf("v is %d \n",v);
    }

    void onConnect(HttpV1ClientInfo) {

    }
    
    void onDisconnect(HttpV1ClientInfo) {
        printf("disconnect!!! \n");
    }


};

int main() {
  MyHttpListener listener = createMyHttpListener();
  HttpV1Server server = createHttpV1Server(8012,listener);
  while(1) {sleep(1000);}
}
