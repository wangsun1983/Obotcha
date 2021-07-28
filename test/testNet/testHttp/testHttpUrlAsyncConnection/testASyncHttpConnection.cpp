
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
#include "HttpUrlConnection.hpp"
#include "HttpUrlAsyncConnectionPool.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(Listener) IMPLEMENTS(HttpAsyncConnectionListener) {
    void onResponse(HttpResponse response) {
        HttpEntity entity = response->getEntity();
        printf("entity is %s \n",entity->getContent()->toValue());
    }

    void onDisconnect() {

    }

    void onConnect(int) {

    }
};

int testAsyncHttpConnection() {

    HttpUrl url = createHttpUrlBuilder()->appendHost(createString("www.tusvisionai.com"))->appendPort(80)->genHttpUrl();
    HttpUrlAsyncConnectionPool pool = createHttpUrlAsyncConnectionPool();

    HttpUrlAsyncConnection connection = pool->createConnection(url,createListener(),nullptr);
    HttpRequest request = createHttpRequest(st(HttpMethod)::Get,url);
    request->getHeader()->setValue(createString("Host"),createString(" www.tusvisionai.com"));
    //for(int i = 0;i < 1024;i++) {
    printf("start wait \n");
    sleep(10);
    
    printf("start send response \n");
    connection->execute(request);
    while(1) {sleep(1000);}
    //}

}
