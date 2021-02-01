
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
#include "HttpCacheControl.hpp"

using namespace obotcha;

int main() {
	HttpUrl url = createHttpUrl();
    HttpRequest request = createHttpRequest(1,url);
	request->setHeader("cache-control","no-cache, max-age=200000");
	HttpCacheControl control = createHttpCacheControl();
	control->import(request->getHeaders());
	printf("max-age is %d \n",control->maxAgeSeconds());
	String value = control->toString();
	printf("value is %s \n",value->toChars());

}
