
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "HttpUrlParser.hpp"
#include "HttpUrl.hpp"
#include "HttpPacket.hpp"
#include "HttpMethod.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "HttpUrlBuilder.hpp"
#include "HttpConnection.hpp"

using namespace obotcha;

DECLARE_CLASS(MyHandler) IMPLEMENTS(Handler) {
public:
    void handleMessage(Message msg) {
        printf("msg id is %d \n",msg->arg1);
        HttpResponse response = Cast<HttpResponse>(msg->data);
        HttpEntity entity = response->getEntity();
        printf("entity is %s \n",entity->getContent()->toValue());
    }
};

int testAsyncHttpConnection() {

    HttpUrl url = createHttpUrlBuilder()->appendHost(createString("www.tusvisionai.com"))->appendPort(80)->genHttpUrl();
    HttpConnection connection = createHttpConnection(url);
    connection->connect();
    HttpRequest request = createHttpRequest(st(HttpMethod)::Get,url);
    request->getHeader()->setValue(createString("Host"),createString(" www.tusvisionai.com"));
    printf("start send response \n");
    HttpResponse response = connection->execute(request);
    if(response != nullptr) {
        printf("it is not nullptr,i is %d \n",1);
    }

    HttpEntity entity = response->getEntity();
    printf("entity is %s \n",entity->getContent()->toValue());
    while(1) {sleep(1000);}

}
