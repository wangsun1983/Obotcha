
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

using namespace obotcha;

//extern int testAsyncHttpConnection();
extern int testSyncHttpConnection();

int main() {
    //testAsyncHttpConnection();
    testSyncHttpConnection();
}
