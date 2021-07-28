
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "TcpClient.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "HttpUrlParser.hpp"
#include "HttpClient.hpp"
#include "HttpUrl.hpp"
#include "HttpPacket.hpp"
#include "HttpMethod.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

using namespace obotcha;




int main() {

    String urlstr = "http://192.168.1.10:8012/abc";
    HttpUrl url = st(HttpUrlParser)::parseUrl(urlstr);
    
    HttpRequest request = createHttpRequest(st(HttpMethod)::Get,url);
    File file = createFile("./request.txt");
    HttpMultiPartFile multifile = createHttpMultiPartFile(file);
    request->addMultiPartFile(multifile);

    //while(1) {
    HttpClient client = createHttpClient();
    HttpResponse response = client->execute(request);
    if(response != nullptr) {
        response->dump();
    }
    //printf("result is %s \n",result->toChars());
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
