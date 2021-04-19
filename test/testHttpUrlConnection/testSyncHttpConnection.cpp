
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

using namespace obotcha;


int testSyncHttpConnection() {

    HttpUrl url = createHttpUrlBuilder()->appendHost(createString("www.tusvisionai.com"))->appendPort(80)->genHttpUrl();
    HttpUrlConnection connection = url->openConnection();
    connection->connect();
    HttpRequest request = createHttpRequest(st(HttpMethod)::Get,url);
    request->getHeader()->setValue(createString("Host"),createString(" www.tusvisionai.com"));
    //for(int i = 0;i < 1024;i++) {
        HttpResponse response = connection->execute(request);
        if(response != nullptr) {
            printf("it is not nullptr,i is %d \n",1);
        }

        HttpEntity entity = response->getEntity();
        printf("entity is %s \n",entity->getContent()->toValue());
    //}

}
