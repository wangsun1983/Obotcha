
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "TcpClient.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "HttpUrlParser.hpp"
#include "HttpClient.hpp"
#include "HttpUrl.hpp"
#include "HttpPacket.hpp"
#include "HttpRequestWriter.hpp"
#include "HttpRequest.hpp"
#include "File.hpp"

using namespace obotcha;

int main() {

    String urlstr = "http://192.168.1.10:8012/log.zip";
    HttpUrl url = st(HttpUrlParser)::parseUrl(urlstr);
    HttpRequest req = createHttpRequest(st(HttpMethod)::Get,url);
	req->addEncodedKeyValue("a1","233");
	req->addEncodedKeyValue("a2","2222");
	//HttpMultiPartFile f1 = createHttpMultiPartFile(createFile("a1.png"));
	//req->addMultiPartFile(f1);
	
	//HttpMultiPartContent content = createHttpMultiPartContent(createString("a2"),createString("b2"));
	//req->addMultiPartContent(content);
	
	HttpRequestWriter writer = createHttpRequestWriter();
	ByteArray arr = writer->compose(req);
	printf("req is %s \n",arr->toString()->toChars());
	while(1){sleep(1000);}

}
