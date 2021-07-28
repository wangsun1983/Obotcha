
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "HttpUrlParser.hpp"

using namespace obotcha;


int main() {
    String request =  "http://su:abc@localhost:1234/test.cgi?a=b&c=d#fffsss";
    HttpUrlParser parser = createHttpUrlParser();
    HttpUrl url = parser->parseUrl(request);
    printf("======= dump start ======= \n");
    url->dump();
    printf("======= dump end ======= \n");
    //parser->parseQuery("q=search&p=123");
    request =  "http://abdd@localhost/test.cgi?a=b&c=d";
    //HttpUrlParser parser = createHttpUrlParser();
    url = parser->parseUrl(request);
    printf("======= dump start ======= \n");
    url->dump();
    printf("======= dump end ======= \n");
    //while(1) {}

    request =  "http://su:abc@localhost/test/wangsl/01234";
    url = parser->parseUrl(request);
    printf("======= dump start ======= \n");
    url->dump();
    printf("======= dump end ======= \n");

}
