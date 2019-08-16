
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "TcpClient.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "HttpUrlParser.hpp"
#include "HttpClient.hpp"
#include "HttpUrl.hpp"

using namespace obotcha;


int main() {

    String urlstr = "http://sina.com.cn";
    HttpUrl url = st(HttpUrlParser)::parseUrl(urlstr);

    HttpClient client = createHttpClient();
    client->execute(0,url);
    while(1){}
/*    
    String request =  "http://su:abc@localhost/test.cgi?a=b&c=d";
    HttpUrlParser parser = createHttpUrlParser();
    parser->parseUrl(request);
    //parser->parseQuery("q=search&p=123");
    request =  "http://abdd@localhost/test.cgi?a=b&c=d";
    //HttpUrlParser parser = createHttpUrlParser();
    parser->parseUrl(request);
    //while(1) {}
*/    

}
