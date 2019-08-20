
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "TcpClient.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "HttpUrlParser.hpp"
#include "HttpClient.hpp"
#include "HttpUrl.hpp"
#include "HttpPacket.hpp"

using namespace obotcha;


int main() {

    String urlstr = "http://www.tusvisionai.com/solutions";
    HttpUrl url = st(HttpUrlParser)::parseUrl(urlstr);

    //while(1) {
    HttpClient client = createHttpClient();
    client->execute(HttpMethodGet,url);
    //}
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
