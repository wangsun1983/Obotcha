
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "TcpClient.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "HttpUrlParser.hpp"

using namespace obotcha;


int main() {
    String request =  "http://localhost/test.cgi?a=b&c=d";
    HttpUrlParser parser = createHttpUrlParser();
    parser->parseUrl(request);
    //parser->parseQuery("q=search&p=123");

    //while(1) {}

}
