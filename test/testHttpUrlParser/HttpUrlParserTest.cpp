
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "TcpClient.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "HttpUrlParser.hpp"

using namespace obotcha;


int main() {
    String request =  "http://baidu.com/post_identity_body_world?q=search&&p=123";
    HttpUrlParser parser = createHttpUrlParser();
    parser->parseUrl(request);

    while(1) {}

}
