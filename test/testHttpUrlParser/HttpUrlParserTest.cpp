
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "TcpClient.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "HttpUrlParser.hpp"

using namespace obotcha;


int main() {
    String request =  "http://su:abc@localhost/test.cgi?a=b&c=d";
    HttpUrlParser parser = createHttpUrlParser();
    parser->parseUrl(request);
    //parser->parseQuery("q=search&p=123");
    request =  "http://abdd@localhost/test.cgi?a=b&c=d";
    //HttpUrlParser parser = createHttpUrlParser();
    parser->parseUrl(request);
    //while(1) {}

}