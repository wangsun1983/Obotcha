#include <stdio.h>
#include <unistd.h>

#include "http_parser.h"

#include "HttpPacketParser.hpp"

using namespace obotcha;

#undef TRUE
#define TRUE 1
#undef FALSE
#define FALSE 0

#define MAX_HEADERS 13
#define MAX_ELEMENT_SIZE 2048
#define MAX_CHUNKS 16

#define MIN(a,b) ((a) < (b) ? (a) : (b))

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*x))

extern "C" {

  struct message {
    const char *name; // for debugging purposes
    const char *raw;
    enum http_parser_type type;
    enum http_method method;
    int status_code;
    char request_url[MAX_ELEMENT_SIZE];
    char response_reason[MAX_ELEMENT_SIZE];
    size_t response_reason_size;
    char body[MAX_ELEMENT_SIZE];
    size_t body_size;
    int num_headers;
    enum { NONE=0, FIELD, VALUE } last_header_element;
    char headers [MAX_HEADERS][2][MAX_ELEMENT_SIZE];
    int should_keep_alive;

    int num_chunks;
    int num_chunks_complete;
    int chunk_lengths[MAX_CHUNKS];

    const char *upgrade; // upgraded body

    unsigned short http_major;
    unsigned short http_minor;

    int message_begin_cb_called;
    int headers_complete_cb_called;
    int message_complete_cb_called;
    int message_complete_on_eof;
  };

  static int currently_parsing_eof;

  static struct message messages[5];
  static int num_messages;

/* * R E S P O N S E S * */
/* * R E S P O N S E S * */
const struct message responses[] =
#define GOOGLE_301 0
{ {.name= "google 301"
  ,.type= HTTP_RESPONSE
  ,.raw= "HTTP/1.1 301 Moved Permanently\r\n"
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
         "</BODY></HTML>\r\n"
  ,.should_keep_alive= TRUE
  ,.message_complete_on_eof= FALSE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 301
  ,.response_reason= "Moved Permanently"
  ,.num_headers= 8
  ,.headers=
    { { "Location", "http://www.google.com/" }
    , { "Content-Type", "text/html; charset=UTF-8" }
    , { "Date", "Sun, 26 Apr 2009 11:11:49 GMT" }
    , { "Expires", "Tue, 26 May 2009 11:11:49 GMT" }
    , { "X-$PrototypeBI-Version", "1.6.0.3" }
    , { "Cache-Control", "public, max-age=2592000" }
    , { "Server", "gws" }
    , { "Content-Length", "219  " }
    }
  ,.body= "<HTML><HEAD><meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\">\n"
          "<TITLE>301 Moved</TITLE></HEAD><BODY>\n"
          "<H1>301 Moved</H1>\n"
          "The document has moved\n"
          "<A HREF=\"http://www.google.com/\">here</A>.\r\n"
          "</BODY></HTML>\r\n"
  }

#define NO_CONTENT_LENGTH_RESPONSE 1
/* The client should wait for the server's EOF. That is, when content-length
 * is not specified, and "Connection: close", the end of body is specified
 * by the EOF.
 * Compare with APACHEBENCH_GET
 */
, {.name= "no content-length response"
  ,.type= HTTP_RESPONSE
  ,.raw= "HTTP/1.1 200 OK\r\n"
         "Date: Tue, 04 Aug 2009 07:59:32 GMT\r\n"
         "Server: Apache\r\n"
         "X-Powered-By: Servlet/2.5 JSP/2.1\r\n"
         "Content-Type: text/xml; charset=utf-8\r\n"
         "Connection: close\r\n"
         "\r\n"
         "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
         "<SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\">\n"
         "  <SOAP-ENV:Body>\n"
         "    <SOAP-ENV:Fault>\n"
         "       <faultcode>SOAP-ENV:Client</faultcode>\n"
         "       <faultstring>Client Error</faultstring>\n"
         "    </SOAP-ENV:Fault>\n"
         "  </SOAP-ENV:Body>\n"
         "</SOAP-ENV:Envelope>"
  ,.should_keep_alive= FALSE
  ,.message_complete_on_eof= TRUE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 200
  ,.response_reason= "OK"
  ,.num_headers= 5
  ,.headers=
    { { "Date", "Tue, 04 Aug 2009 07:59:32 GMT" }
    , { "Server", "Apache" }
    , { "X-Powered-By", "Servlet/2.5 JSP/2.1" }
    , { "Content-Type", "text/xml; charset=utf-8" }
    , { "Connection", "close" }
    }
  ,.body= "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
          "<SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\">\n"
          "  <SOAP-ENV:Body>\n"
          "    <SOAP-ENV:Fault>\n"
          "       <faultcode>SOAP-ENV:Client</faultcode>\n"
          "       <faultstring>Client Error</faultstring>\n"
          "    </SOAP-ENV:Fault>\n"
          "  </SOAP-ENV:Body>\n"
          "</SOAP-ENV:Envelope>"
  }

#define NO_HEADERS_NO_BODY_404 2
, {.name= "404 no headers no body"
  ,.type= HTTP_RESPONSE
  ,.raw= "HTTP/1.1 404 Not Found\r\n\r\n"
  ,.should_keep_alive= FALSE
  ,.message_complete_on_eof= TRUE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 404
  ,.response_reason= "Not Found"
  ,.num_headers= 0 ,.headers= {}
  ,.body_size= 0
  ,.body= ""
  }

#define NO_REASON_PHRASE 3
, {.name= "304 no response phrase"
  ,.type= HTTP_RESPONSE
  ,.raw= "HTTP/1.1 304\r\n\r\n"
  ,.should_keep_alive = TRUE
  ,.message_complete_on_eof= FALSE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 304
  ,.response_reason= ""
  ,.num_headers= 0
  ,.headers= {}
  ,.body= ""
  }

#define TRAILING_SPACE_ON_CHUNKED_BODY 4
, {.name="200 trailing space on chunked body"
  ,.type= HTTP_RESPONSE
  ,.raw= "HTTP/1.1 200 OK\r\n"
         "Content-Type: text/plain\r\n"
         "Transfer-Encoding: chunked\r\n"
         "\r\n"
         "25  \r\n"
         "This is the data in the first chunk\r\n"
         "\r\n"
         "1C\r\n"
         "and this is the second one\r\n"
         "\r\n"
         "0  \r\n"
         "\r\n"
  ,.should_keep_alive= TRUE
  ,.message_complete_on_eof= FALSE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 200
  ,.response_reason= "OK"
  ,.num_headers= 2
  ,.headers=
    { {"Content-Type", "text/plain" }
    , {"Transfer-Encoding", "chunked" }
    }
  ,.body_size = 37+28
  ,.body =
         "This is the data in the first chunk\r\n"
         "and this is the second one\r\n"
  ,.num_chunks= 2
  ,.num_chunks_complete= 3
  ,.chunk_lengths= { 0x25, 0x1c }

  }

#define NO_CARRIAGE_RET 5
, {.name="no carriage ret"
  ,.type= HTTP_RESPONSE
  ,.raw= "HTTP/1.1 200 OK\n"
         "Content-Type: text/html; charset=utf-8\n"
         "Connection: close\n"
         "\n"
         "these headers are from http://news.ycombinator.com/"
  ,.should_keep_alive= FALSE
  ,.message_complete_on_eof= TRUE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 200
  ,.response_reason= "OK"
  ,.num_headers= 2
  ,.headers=
    { {"Content-Type", "text/html; charset=utf-8" }
    , {"Connection", "close" }
    }
  ,.body= "these headers are from http://news.ycombinator.com/"
  }

#define PROXY_CONNECTION 6
, {.name="proxy connection"
  ,.type= HTTP_RESPONSE
  ,.raw= "HTTP/1.1 200 OK\r\n"
         "Content-Type: text/html; charset=UTF-8\r\n"
         "Content-Length: 11\r\n"
         "Proxy-Connection: close\r\n"
         "Date: Thu, 31 Dec 2009 20:55:48 +0000\r\n"
         "\r\n"
         "hello world"
  ,.should_keep_alive= FALSE
  ,.message_complete_on_eof= FALSE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 200
  ,.response_reason= "OK"
  ,.num_headers= 4
  ,.headers=
    { {"Content-Type", "text/html; charset=UTF-8" }
    , {"Content-Length", "11" }
    , {"Proxy-Connection", "close" }
    , {"Date", "Thu, 31 Dec 2009 20:55:48 +0000"}
    }
  ,.body= "hello world"
  }

#define UNDERSTORE_HEADER_KEY 7
  // shown by
  // curl -o /dev/null -v "http://ad.doubleclick.net/pfadx/DARTSHELLCONFIGXML;dcmt=text/xml;"
, {.name="underscore header key"
  ,.type= HTTP_RESPONSE
  ,.raw= "HTTP/1.1 200 OK\r\n"
         "Server: DCLK-AdSvr\r\n"
         "Content-Type: text/xml\r\n"
         "Content-Length: 0\r\n"
         "DCLK_imp: v7;x;114750856;0-0;0;17820020;0/0;21603567/21621457/1;;~okv=;dcmt=text/xml;;~cs=o\r\n\r\n"
  ,.should_keep_alive= TRUE
  ,.message_complete_on_eof= FALSE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 200
  ,.response_reason= "OK"
  ,.num_headers= 4
  ,.headers=
    { {"Server", "DCLK-AdSvr" }
    , {"Content-Type", "text/xml" }
    , {"Content-Length", "0" }
    , {"DCLK_imp", "v7;x;114750856;0-0;0;17820020;0/0;21603567/21621457/1;;~okv=;dcmt=text/xml;;~cs=o" }
    }
  ,.body= ""
  }

#define BONJOUR_MADAME_FR 8
/* The client should not merge two headers fields when the first one doesn't
 * have a value.
 */
, {.name= "bonjourmadame.fr"
  ,.type= HTTP_RESPONSE
  ,.raw= "HTTP/1.0 301 Moved Permanently\r\n"
         "Date: Thu, 03 Jun 2010 09:56:32 GMT\r\n"
         "Server: Apache/2.2.3 (Red Hat)\r\n"
         "Cache-Control: public\r\n"
         "Pragma: \r\n"
         "Location: http://www.bonjourmadame.fr/\r\n"
         "Vary: Accept-Encoding\r\n"
         "Content-Length: 0\r\n"
         "Content-Type: text/html; charset=UTF-8\r\n"
         "Connection: keep-alive\r\n"
         "\r\n"
  ,.should_keep_alive= TRUE
  ,.message_complete_on_eof= FALSE
  ,.http_major= 1
  ,.http_minor= 0
  ,.status_code= 301
  ,.response_reason= "Moved Permanently"
  ,.num_headers= 9
  ,.headers=
    { { "Date", "Thu, 03 Jun 2010 09:56:32 GMT" }
    , { "Server", "Apache/2.2.3 (Red Hat)" }
    , { "Cache-Control", "public" }
    , { "Pragma", "" }
    , { "Location", "http://www.bonjourmadame.fr/" }
    , { "Vary",  "Accept-Encoding" }
    , { "Content-Length", "0" }
    , { "Content-Type", "text/html; charset=UTF-8" }
    , { "Connection", "keep-alive" }
    }
  ,.body= ""
  }

#define RES_FIELD_UNDERSCORE 10
/* Should handle spaces in header fields */
, {.name= "field underscore"
  ,.type= HTTP_RESPONSE
  ,.raw= "HTTP/1.1 200 OK\r\n"
         "Date: Tue, 28 Sep 2010 01:14:13 GMT\r\n"
         "Server: Apache\r\n"
         "Cache-Control: no-cache, must-revalidate\r\n"
         "Expires: Mon, 26 Jul 1997 05:00:00 GMT\r\n"
         ".et-Cookie: PlaxoCS=1274804622353690521; path=/; domain=.plaxo.com\r\n"
         "Vary: Accept-Encoding\r\n"
         "_eep-Alive: timeout=45\r\n" /* semantic value ignored */
         "_onnection: Keep-Alive\r\n" /* semantic value ignored */
         "Transfer-Encoding: chunked\r\n"
         "Content-Type: text/html\r\n"
         "Connection: close\r\n"
         "\r\n"
         "0\r\n\r\n"
  ,.should_keep_alive= FALSE
  ,.message_complete_on_eof= FALSE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 200
  ,.response_reason= "OK"
  ,.num_headers= 11
  ,.headers=
    { { "Date", "Tue, 28 Sep 2010 01:14:13 GMT" }
    , { "Server", "Apache" }
    , { "Cache-Control", "no-cache, must-revalidate" }
    , { "Expires", "Mon, 26 Jul 1997 05:00:00 GMT" }
    , { ".et-Cookie", "PlaxoCS=1274804622353690521; path=/; domain=.plaxo.com" }
    , { "Vary", "Accept-Encoding" }
    , { "_eep-Alive", "timeout=45" }
    , { "_onnection", "Keep-Alive" }
    , { "Transfer-Encoding", "chunked" }
    , { "Content-Type", "text/html" }
    , { "Connection", "close" }
    }
  ,.body= ""
  ,.num_chunks= 0
  ,.num_chunks_complete= 1
  ,.chunk_lengths= {}
  }

#define NON_ASCII_IN_STATUS_LINE 11
/* Should handle non-ASCII in status line */
, {.name= "non-ASCII in status line"
  ,.type= HTTP_RESPONSE
  ,.raw= "HTTP/1.1 500 Oriëntatieprobleem\r\n"
         "Date: Fri, 5 Nov 2010 23:07:12 GMT+2\r\n"
         "Content-Length: 0\r\n"
         "Connection: close\r\n"
         "\r\n"
  ,.should_keep_alive= FALSE
  ,.message_complete_on_eof= FALSE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 500
  ,.response_reason= "Oriëntatieprobleem"
  ,.num_headers= 3
  ,.headers=
    { { "Date", "Fri, 5 Nov 2010 23:07:12 GMT+2" }
    , { "Content-Length", "0" }
    , { "Connection", "close" }
    }
  ,.body= ""
  }
};
}

int main() {
    //struct message requests
    int size = sizeof(responses)/sizeof(struct message);
    printf("size is %d \n",size);

    for(int i = 0;i<size;i++) {
      printf("////HttpPacketParser start %d ////\n",i);
      HttpPacketParser parser = createHttpPacketParser();
      struct message msg = responses[i];
      parser->pushHttpData(createByteArray((const byte *)msg.raw,strlen(msg.raw)));
      ArrayList<HttpPacket> packets = parser->doParse();
      if(packets->size() != 1) {
        printf("HttpPacketParser Test1 Fail,index is %d,content is %s,size is %d \n",i,msg.raw,packets->size());
        continue;
      }
      //check method
      HttpPacket packet = packets->get(0);
      if(packet->getHeader()->getType() != st(HttpHeader)::Response) {
        printf("HttpPacketParser Test2 Fail,type is %d \n",packet->getHeader()->getType());
        continue;
      }

      //check url
      if(packet->getHeader()->getResponseStatus() != msg.status_code) {
        printf("HttpPacketParser Test3 Fail,response status is %d,msg.status_code is %d \n",packet->getHeader()->getResponseStatus(),msg.status_code);
        continue;
      }
	  
	   //check reason
	   if(packet->getHeader()->getResponseReason() == nullptr) {
		   printf("HttpPacketParser Test4 Warning,response reason null\n");
	   } else if(!packet->getHeader()->getResponseReason()->equals(createString(msg.response_reason))) {
        printf("HttpPacketParser Test4 Fail,response status is %s,msg.reason is %s \n",packet->getHeader()->getResponseReason()->toChars(),msg.response_reason);
        continue;
      }
	  
      //check header
      int headersize = msg.num_headers;
      for(int i = 0;i<headersize;i++) {
        char *key = msg.headers[i][0];
        char *value = msg.headers[i][1];
        String fValue = packet->getHeader()->getValue(createString(key)->toLowerCase());
        if(fValue == nullptr) {
          printf("HttpPacketParser Test5 Fail,packet value is null,key is %s \n",key);
          continue;
        }

        if(!fValue->equals(value)) {
          printf("HttpPacketParser Test6 Fail,packet value is %s,length is %d,msg value is %s,length is %d \n",fValue->toChars(),fValue->size(),value,strlen(value));
          for(int i = 0;i < fValue->size();i++) {
            printf("v is %c \n",fValue->toChars()[i]);
          }
          continue;
        }
      }
      //check Version
      HttpVersion version = packet->getHeader()->getVersion();
      if(version->getMajorVer() != msg.http_major || version->getMinorVer() != msg.http_minor) {
        printf("HttpPacketParser Test7 Fail,packet version is %d.%d,msg version is %d.%d \n",
                version->getMajorVer(),version->getMinorVer(),msg.http_major,msg.http_minor);
        continue;
      }
      //check content
      HttpEntity entity = packet->getEntity();
      if(strlen(msg.body) > 0) {
        printf("trace4_1 \n");
        if(entity == nullptr) {
          printf("HttpPacketParser Test8 Fail,packet entity is null\n");
          continue;
        }
        String content = entity->getContent()->toString();
        printf("trace4_2 \n");
        if(content == nullptr) {
          printf("HttpPacketParser Test7 Fail,packet content is null\n");
        } else if(!content->equals(msg.body)) {
          printf("HttpPacketParser Test8 Fail,packet content is %s,size is %d \n",content->toChars(),content->size());
          printf("HttpPacketParser Test8 Fail,msg content is %s,size is %d \n",msg.body,strlen(msg.body));
        }
      } else {
        if(entity != nullptr && entity->getContent() != nullptr) {
          printf("HttpPacketParser Test9 Fail,packet content is %s\n",entity->getContent()->toString()->toChars());
        }
      }
    }

}
