
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

    HttpUrl url = createHttpUrlBuilder()->appendPort(9090)->genHttpUrl();
    HttpConnection connection = createHttpConnection(url);
    connection->connect();
    HttpRequest request = createHttpRequest(st(HttpMethod)::Get,url);
    request->getHeader()->setValue(createString("Host"),createString(" www.tusvisionai.com"));
    
    HttpResponse response = connection->execute(request);

    HttpEntity entity = response->getEntity();
    printf("entity is %s \n",entity->getContent()->toValue());
    String value = entity->getContent()->toString();
    if(value == nullptr || !value->equals("Hello this is server!")) {
        printf("---TestHttpConnection Sync test1 [FAILED]--- \n");
        return 0;
    }

    printf("---TestHttpConnection Sync test100 [OK]--- \n");
    return 0;
}
