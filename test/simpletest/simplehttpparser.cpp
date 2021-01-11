#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"
#include "CipherCreator.hpp"
#include "SecretKeyCreator.hpp"
#include "File.hpp"
#include "HttpV1Parser.hpp"
#include "HttpPacket.hpp"
#include "ArrayList.hpp"

using namespace obotcha;
#if 0
GET /login HTTP/1.1
Content-Type: application/x-www-form-urlencoded
User-Agent: PostmanRuntime/7.22.0
Accept: */*
Cache-Control: no-cache
Postman-Token: ff565c13-4cb0-4b67-b564-3366153e8fbf
Host: 192.168.1.10:8012
Accept-Encoding: gzip, deflate, br
Content-Length: 14
Connection: keep-alive

a1=233&a2=2222
#endif

#if 0
HttpDispatchRunnable run trace1,data->pack is GET /login HTTP/1.1
Content-Type: multipart/form-data; boundary=--------------------------712541294259138523003686
User-Agent: PostmanRuntime/7.22.0
Accept: */*
Cache-Control: no-cache
Postman-Token: 94c4bcd5-cf66-4e2f-809c-24771c74f0df
Host: 192.168.1.10:8012
Accept-Encoding: gzip, deflate, br
Content-Length: 492
Connection: keep-alive

----------------------------712541294259138523003686
Content-Disposition: form-data; name="1"

1111
----------------------------712541294259138523003686
Content-Disposition: form-data; name="f1"; filename=""


----------------------------712541294259138523003686
Content-Disposition: form-data; name="2"

2222
----------------------------712541294259138523003686
Content-Disposition: form-data; name="f2"; filename=""


----------------------------712541294259138523003686--
 
#endif

int main() {

    char *http = "HTTP/1.1 301 Moved Permanently\r\n"
         "Location: http://www.google.com/\r\n"
         "Content-Type: text/html; charset=UTF-8\r\n"
         "Date: Sun, 26 Apr 2009 11:11:49 GMT\r\n"
         "Expires: Tue, 26 May 2009 11:11:49 GMT\r\n"
         "X-$PrototypeBI-Version: 1.6.0.3\r\n" /* $ char in header field */
         "Cache-Control: public, max-age=2592000\r\n"
         "Server: gws\r\n"
         "Content-Length:  219  \r\n"
         "\r\n"
         "<HTML><HEAD><meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\">\n"
         "<TITLE>301 Moved</TITLE></HEAD><BODY>\n"
         "<H1>301 Moved</H1>\n"
         "The document has moved\n"
         "<A HREF=\"http://www.google.com/\">here</A>.\r\n"
         "</BODY></HTML>\r\n";
    String data = createString(http);

    //printf("content is %s \n",http);

    HttpV1Parser parser = createHttpV1Parser();
    parser->pushHttpData(createByteArray(data));
    ArrayList<HttpPacket> list = parser->doParse();
    if(list != nullptr) {
      printf("list size is %d \n",list->size());
    }

}
