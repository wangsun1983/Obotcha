
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
#include "CountDownLatch.hpp"
#include "HttpConnectionListener.hpp"

using namespace obotcha;

CountDownLatch latch = createCountDownLatch(1);
String value;


DECLARE_CLASS(MyListener) IMPLEMENTS(HttpConnectionListener) {
public:
    void onResponse(HttpResponse response) {
        HttpEntity entity = response->getEntity();
        value = entity->getContent()->toString();
        printf("value is %s \n",value->toChars());
        latch->countDown();
    }

    void onDisconnect() {
        
    }
    
    void onConnect() {}
        
};

int main() {

    HttpUrl url = createHttpUrlBuilder()->appendPort(9090)->genHttpUrl();
    HttpConnection connection = createHttpConnection(url,nullptr,true,createMyListener());
    int ret = connection->connect();
    printf("ret is %d \n",ret);

    HttpRequest request = createHttpRequest(st(HttpMethod)::Get,url);
    request->getHeader()->setValue(createString("Host"),createString(" www.tusvisionai.com"));
    printf("start send response \n");
    HttpResponse response = connection->execute(request);
    if(response != nullptr) {
        printf("it is not nullptr,i is %d \n",1);
    }

    latch->await();
    if(value == nullptr || !value->equals("Hello this is server!")) {
        printf("---TestHttpConnection Async test1 [FAILED]--- \n");
        return 0;
    }

    printf("---TestHttpConnection Async test100 [OK]--- \n");
    return 0;

}
