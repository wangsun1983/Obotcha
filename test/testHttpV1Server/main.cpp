#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"
#include "HttpV1Server.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyHttpListener) IMPLEMENTS(HttpV1Listener) {
public:
    void onMessage(HttpV1ClientInfo client,HttpPacket msg) {
        if(msg->getBody()!= nullptr) {
            printf("msg is %s \n",msg->getBody()->toValue());
        }
        
        HttpPacket response = createHttpPacket();
        response->getHeader()->setValue(st(HttpHeader)::Status,"200");//setHeaderValue(Http_Header_Status,"200");

        String body = createString("<h1>Response from Gagira</h1>");
        body = body->append("<h2>Response from Gagira</h2> \r\n");
        body = body->append("<h3>Response from Gagira</h3> \r\n");

        //response->setHeaderValue(Http_Header_Content_Length,createString(body->size()));
        response->getHeader()->setValue(st(HttpHeader)::ContentLength,createString(body->size()));
        response->setBody(createByteArray(body));
        String resp = response->genHttpResponse();

        int v = client->send(resp);
        printf("v is %d \n",v);
    }
};

int main() {
  MyHttpListener listener = createMyHttpListener();
  HttpV1Server server = createHttpV1Server(8012,listener);
  while(1) {sleep(1000);}
}
