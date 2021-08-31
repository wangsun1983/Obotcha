
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

int main() {

    HttpUrl url = createHttpUrlBuilder()->appendHost(createString("192.168.1.10"))->appendPort(9090)->genHttpUrl();
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
