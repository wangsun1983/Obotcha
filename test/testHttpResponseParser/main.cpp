#include <stdio.h>
#include <unistd.h>

#include "HttpPacketParser.hpp"
#include "HttpMethod.hpp"
#include "HttpHeader.hpp"

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
  int type;
  int method;
  int status_code;
  char response_status[MAX_ELEMENT_SIZE];
  char request_path[MAX_ELEMENT_SIZE];
  char request_url[MAX_ELEMENT_SIZE];
  char fragment[MAX_ELEMENT_SIZE];
  char query_string[MAX_ELEMENT_SIZE];
  char body[MAX_ELEMENT_SIZE];
  size_t body_size;
  const char *host;
  const char *userinfo;
  uint16_t port;
  int num_headers;
  enum { NONE=0, FIELD, VALUE } last_header_element;
  char headers [MAX_HEADERS][2][MAX_ELEMENT_SIZE];
  int should_keep_alive;

  int num_chunks;
  int num_chunks_complete;
  int chunk_lengths[MAX_CHUNKS];

  const char *key_value[MAX_ELEMENT_SIZE];
  int key_value_size;

  const char *upgrade; // upgraded body

  unsigned short http_major;
  unsigned short http_minor;
  int content_length;

  int message_begin_cb_called;
  int headers_complete_cb_called;
  int message_complete_cb_called;
  int status_cb_called;
  int message_complete_on_eof;
  int body_is_final;
  int allow_chunked_length;
};



static struct message messages[5];
static int num_messages;

/* * R E S P O N S E S * */
const struct message responses[] =
#define GOOGLE_301 0
{ {.name= "google 301"
  ,.type= st(HttpHeader)::Type::Response
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
  ,.response_status= "Moved Permanently"
  ,.content_length= 219
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
  ,.type= st(HttpHeader)::Type::Response
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
  ,.response_status= "OK"
  ,.content_length= -1
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
  ,.type= st(HttpHeader)::Type::Response
  ,.raw= "HTTP/1.1 404 Not Found\r\n\r\n"
  ,.should_keep_alive= FALSE
  ,.message_complete_on_eof= TRUE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 404
  ,.response_status= "Not Found"
  ,.content_length= -1
  ,.num_headers= 0
  ,.headers= {}
  ,.body_size= 0
  ,.body= ""
  }

#define NO_REASON_PHRASE 3
, {.name= "301 no response phrase"
  ,.type= st(HttpHeader)::Type::Response
  ,.raw= "HTTP/1.1 301\r\n\r\n"
  ,.should_keep_alive = FALSE
  ,.message_complete_on_eof= TRUE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 301
  ,.content_length= -1
  ,.response_status= ""
  ,.num_headers= 0
  ,.headers= {}
  ,.body= ""
  }

#define TRAILING_SPACE_ON_CHUNKED_BODY 4
, {.name="200 trailing space on chunked body"
  ,.type= st(HttpHeader)::Type::Response
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
  ,.response_status= "OK"
  ,.content_length= -1
  ,.num_headers= 2
  ,.headers=
    { {"Content-Type", "text/plain" }
    , {"Transfer-Encoding", "chunked" }
    }
  ,.body_size = 37+28
  ,.body =
         "This is the data in the first chunk\r\n"
         "and this is the second one\r\n"
  ,.num_chunks_complete= 3
  ,.chunk_lengths= { 0x25, 0x1c }
  }

#define NO_CARRIAGE_RET 5
, {.name="no carriage ret"
  ,.type= st(HttpHeader)::Type::Response
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
  ,.response_status= "OK"
  ,.content_length= -1
  ,.num_headers= 2
  ,.headers=
    { {"Content-Type", "text/html; charset=utf-8" }
    , {"Connection", "close" }
    }
  ,.body= "these headers are from http://news.ycombinator.com/"
  }

#define PROXY_CONNECTION 6
, {.name="proxy connection"
  ,.type= st(HttpHeader)::Type::Response
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
  ,.response_status= "OK"
  ,.content_length= 11
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
  ,.type= st(HttpHeader)::Type::Response
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
  ,.response_status= "OK"
  ,.content_length= 0
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
  ,.type= st(HttpHeader)::Type::Response
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
  ,.response_status= "Moved Permanently"
  ,.content_length= 0
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

#define RES_FIELD_UNDERSCORE 9
/* Should handle spaces in header fields */
, {.name= "field underscore"
  ,.type= st(HttpHeader)::Type::Response
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
  ,.response_status= "OK"
  ,.content_length= -1
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
  ,.num_chunks_complete= 1
  ,.chunk_lengths= {}
  }

#define NON_ASCII_IN_STATUS_LINE 10
/* Should handle non-ASCII in status line */
, {.name= "non-ASCII in status line"
  ,.type= st(HttpHeader)::Type::Response
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
  ,.response_status= "Oriëntatieprobleem"
  ,.content_length= 0
  ,.num_headers= 3
  ,.headers=
    { { "Date", "Fri, 5 Nov 2010 23:07:12 GMT+2" }
    , { "Content-Length", "0" }
    , { "Connection", "close" }
    }
  ,.body= ""
  }

#define HTTP_VERSION_0_9 11
/* Should handle HTTP/0.9 */
, {.name= "http version 0.9"
  ,.type= st(HttpHeader)::Type::Response
  ,.raw= "HTTP/0.9 200 OK\r\n"
         "\r\n"
  ,.should_keep_alive= FALSE
  ,.message_complete_on_eof= TRUE
  ,.http_major= 0
  ,.http_minor= 9
  ,.status_code= 200
  ,.response_status= "OK"
  ,.content_length= -1
  ,.num_headers= 0
  ,.headers=
    {}
  ,.body= ""
  }

#define NO_CONTENT_LENGTH_NO_TRANSFER_ENCODING_RESPONSE 12
/* The client should wait for the server's EOF. That is, when neither
 * content-length nor transfer-encoding is specified, the end of body
 * is specified by the EOF.
 */
, {.name= "neither content-length nor transfer-encoding response"
  ,.type= st(HttpHeader)::Type::Response
  ,.raw= "HTTP/1.1 200 OK\r\n"
         "Content-Type: text/plain\r\n"
         "\r\n"
         "hello world"
  ,.should_keep_alive= FALSE
  ,.message_complete_on_eof= TRUE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 200
  ,.response_status= "OK"
  ,.content_length= -1
  ,.num_headers= 1
  ,.headers=
    { { "Content-Type", "text/plain" }
    }
  ,.body= "hello world"
  }

#define NO_BODY_HTTP10_KA_200 13
, {.name= "HTTP/1.0 with keep-alive and EOF-terminated 200 status"
  ,.type= st(HttpHeader)::Type::Response
  ,.raw= "HTTP/1.0 200 OK\r\n"
         "Connection: keep-alive\r\n"
         "\r\n"
  ,.should_keep_alive= FALSE
  ,.message_complete_on_eof= TRUE
  ,.http_major= 1
  ,.http_minor= 0
  ,.status_code= 200
  ,.response_status= "OK"
  ,.content_length= -1
  ,.num_headers= 1
  ,.headers=
    { { "Connection", "keep-alive" }
    }
  ,.body_size= 0
  ,.body= ""
  }

#define NO_BODY_HTTP10_KA_204 14
, {.name= "HTTP/1.0 with keep-alive and a 204 status"
  ,.type= st(HttpHeader)::Type::Response
  ,.raw= "HTTP/1.0 204 No content\r\n"
         "Connection: keep-alive\r\n"
         "\r\n"
  ,.should_keep_alive= TRUE
  ,.message_complete_on_eof= FALSE
  ,.http_major= 1
  ,.http_minor= 0
  ,.status_code= 204
  ,.response_status= "No content"
  ,.content_length= -1
  ,.num_headers= 1
  ,.headers=
    { { "Connection", "keep-alive" }
    }
  ,.body_size= 0
  ,.body= ""
  }

#define NO_BODY_HTTP11_KA_200 15
, {.name= "HTTP/1.1 with an EOF-terminated 200 status"
  ,.type= st(HttpHeader)::Type::Response
  ,.raw= "HTTP/1.1 200 OK\r\n"
         "\r\n"
  ,.should_keep_alive= FALSE
  ,.message_complete_on_eof= TRUE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 200
  ,.response_status= "OK"
  ,.content_length= -1
  ,.num_headers= 0
  ,.headers={}
  ,.body_size= 0
  ,.body= ""
  }

#define NO_BODY_HTTP11_KA_204 16
, {.name= "HTTP/1.1 with a 204 status"
  ,.type= st(HttpHeader)::Type::Response
  ,.raw= "HTTP/1.1 204 No content\r\n"
         "\r\n"
  ,.should_keep_alive= TRUE
  ,.message_complete_on_eof= FALSE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 204
  ,.response_status= "No content"
  ,.content_length= -1
  ,.num_headers= 0
  ,.headers={}
  ,.body_size= 0
  ,.body= ""
  }

#define NO_BODY_HTTP11_NOKA_204 17
, {.name= "HTTP/1.1 with a 204 status and keep-alive disabled"
  ,.type= st(HttpHeader)::Type::Response
  ,.raw= "HTTP/1.1 204 No content\r\n"
         "Connection: close\r\n"
         "\r\n"
  ,.should_keep_alive= FALSE
  ,.message_complete_on_eof= FALSE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 204
  ,.response_status= "No content"
  ,.content_length= -1
  ,.num_headers= 1
  ,.headers=
    { { "Connection", "close" }
    }
  ,.body_size= 0
  ,.body= ""
  }

#define NO_BODY_HTTP11_KA_CHUNKED_200 18
, {.name= "HTTP/1.1 with chunked endocing and a 200 response"
  ,.type= st(HttpHeader)::Type::Response
  ,.raw= "HTTP/1.1 200 OK\r\n"
         "Transfer-Encoding: chunked\r\n"
         "\r\n"
         "0\r\n"
         "\r\n"
  ,.should_keep_alive= TRUE
  ,.message_complete_on_eof= FALSE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 200
  ,.response_status= "OK"
  ,.content_length= -1
  ,.num_headers= 1
  ,.headers=
    { { "Transfer-Encoding", "chunked" }
    }
  ,.body_size= 0
  ,.body= ""
  ,.num_chunks_complete= 1
  }

#if !HTTP_PARSER_STRICT
#define SPACE_IN_FIELD_RES 19
/* Should handle spaces in header fields */
, {.name= "field space"
  ,.type= st(HttpHeader)::Type::Response
  ,.raw= "HTTP/1.1 200 OK\r\n"
         "Server: Microsoft-IIS/6.0\r\n"
         "X-Powered-By: ASP.NET\r\n"
         "en-US Content-Type: text/xml\r\n" /* this is the problem */
         "Content-Type: text/xml\r\n"
         "Content-Length: 16\r\n"
         "Date: Fri, 23 Jul 2010 18:45:38 GMT\r\n"
         "Connection: keep-alive\r\n"
         "\r\n"
         "<xml>hello</xml>" /* fake body */
  ,.should_keep_alive= TRUE
  ,.message_complete_on_eof= FALSE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 200
  ,.response_status= "OK"
  ,.content_length= 16
  ,.num_headers= 7
  ,.headers=
    { { "Server",  "Microsoft-IIS/6.0" }
    , { "X-Powered-By", "ASP.NET" }
    , { "en-US Content-Type", "text/xml" }
    , { "Content-Type", "text/xml" }
    , { "Content-Length", "16" }
    , { "Date", "Fri, 23 Jul 2010 18:45:38 GMT" }
    , { "Connection", "keep-alive" }
    }
  ,.body= "<xml>hello</xml>"
  }
#endif /* !HTTP_PARSER_STRICT */

#define AMAZON_COM 20
, {.name= "amazon.com"
  ,.type= st(HttpHeader)::Type::Response
  ,.raw= "HTTP/1.1 301 MovedPermanently\r\n"
         "Date: Wed, 15 May 2013 17:06:33 GMT\r\n"
         "Server: Server\r\n"
         "x-amz-id-1: 0GPHKXSJQ826RK7GZEB2\r\n"
         "p3p: policyref=\"http://www.amazon.com/w3c/p3p.xml\",CP=\"CAO DSP LAW CUR ADM IVAo IVDo CONo OTPo OUR DELi PUBi OTRi BUS PHY ONL UNI PUR FIN COM NAV INT DEM CNT STA HEA PRE LOC GOV OTC \"\r\n"
         "x-amz-id-2: STN69VZxIFSz9YJLbz1GDbxpbjG6Qjmmq5E3DxRhOUw+Et0p4hr7c/Q8qNcx4oAD\r\n"
         "Location: http://www.amazon.com/Dan-Brown/e/B000AP9DSU/ref=s9_pop_gw_al1?_encoding=UTF8&refinementId=618073011&pf_rd_m=ATVPDKIKX0DER&pf_rd_s=center-2&pf_rd_r=0SHYY5BZXN3KR20BNFAY&pf_rd_t=101&pf_rd_p=1263340922&pf_rd_i=507846\r\n"
         "Vary: Accept-Encoding,User-Agent\r\n"
         "Content-Type: text/html; charset=ISO-8859-1\r\n"
         "Transfer-Encoding: chunked\r\n"
         "\r\n"
         "1\r\n"
         "\n\r\n"
         "0\r\n"
         "\r\n"
  ,.should_keep_alive= TRUE
  ,.message_complete_on_eof= FALSE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 301
  ,.response_status= "MovedPermanently"
  ,.content_length= -1
  ,.num_headers= 9
  ,.headers= { { "Date", "Wed, 15 May 2013 17:06:33 GMT" }
             , { "Server", "Server" }
             , { "x-amz-id-1", "0GPHKXSJQ826RK7GZEB2" }
             , { "p3p", "policyref=\"http://www.amazon.com/w3c/p3p.xml\",CP=\"CAO DSP LAW CUR ADM IVAo IVDo CONo OTPo OUR DELi PUBi OTRi BUS PHY ONL UNI PUR FIN COM NAV INT DEM CNT STA HEA PRE LOC GOV OTC \"" }
             , { "x-amz-id-2", "STN69VZxIFSz9YJLbz1GDbxpbjG6Qjmmq5E3DxRhOUw+Et0p4hr7c/Q8qNcx4oAD" }
             , { "Location", "http://www.amazon.com/Dan-Brown/e/B000AP9DSU/ref=s9_pop_gw_al1?_encoding=UTF8&refinementId=618073011&pf_rd_m=ATVPDKIKX0DER&pf_rd_s=center-2&pf_rd_r=0SHYY5BZXN3KR20BNFAY&pf_rd_t=101&pf_rd_p=1263340922&pf_rd_i=507846" }
             , { "Vary", "Accept-Encoding,User-Agent" }
             , { "Content-Type", "text/html; charset=ISO-8859-1" }
             , { "Transfer-Encoding", "chunked" }
             }
  ,.body= "\n"
  ,.num_chunks_complete= 2
  ,.chunk_lengths= { 1 }
  }

#define EMPTY_REASON_PHRASE_AFTER_SPACE 21
, {.name= "empty reason phrase after space"
  ,.type= st(HttpHeader)::Type::Response
  ,.raw= "HTTP/1.1 200 \r\n"
         "\r\n"
  ,.should_keep_alive= FALSE
  ,.message_complete_on_eof= TRUE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 200
  ,.response_status= ""
  ,.content_length= -1
  ,.num_headers= 0
  ,.headers= {}
  ,.body= ""
  }

#define CONTENT_LENGTH_X 22
, {.name= "Content-Length-X"
  ,.type= st(HttpHeader)::Type::Response
  ,.raw= "HTTP/1.1 200 OK\r\n"
         "Content-Length-X: 0\r\n"
         "Transfer-Encoding: chunked\r\n"
         "\r\n"
         "2\r\n"
         "OK\r\n"
         "0\r\n"
         "\r\n"
  ,.should_keep_alive= TRUE
  ,.message_complete_on_eof= FALSE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 200
  ,.response_status= "OK"
  ,.content_length= -1
  ,.num_headers= 2
  ,.headers= { { "Content-Length-X", "0" }
             , { "Transfer-Encoding", "chunked" }
             }
  ,.body= "OK"
  ,.num_chunks_complete= 2
  ,.chunk_lengths= { 2 }
  }

#define HTTP_101_RESPONSE_WITH_UPGRADE_HEADER 23
, {.name= "HTTP 101 response with Upgrade header"
  ,.type= st(HttpHeader)::Type::Response
  ,.raw= "HTTP/1.1 101 Switching Protocols\r\n"
         "Connection: upgrade\r\n"
         "Upgrade: h2c\r\n"
         "\r\n"
         "proto"
  ,.should_keep_alive= TRUE
  ,.message_complete_on_eof= FALSE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 101
  ,.response_status= "Switching Protocols"
  ,.upgrade= "proto"
  ,.content_length= -1
  ,.num_headers= 2
  ,.headers=
    { { "Connection", "upgrade" }
    , { "Upgrade", "h2c" }
    }
  }

#define HTTP_101_RESPONSE_WITH_UPGRADE_HEADER_AND_CONTENT_LENGTH 24
, {.name= "HTTP 101 response with Upgrade and Content-Length header"
  ,.type= st(HttpHeader)::Type::Response
  ,.raw= "HTTP/1.1 101 Switching Protocols\r\n"
         "Connection: upgrade\r\n"
         "Upgrade: h2c\r\n"
         "Content-Length: 4\r\n"
         "\r\n"
         "body"
         "proto"
  ,.should_keep_alive= TRUE
  ,.message_complete_on_eof= FALSE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 101
  ,.response_status= "Switching Protocols"
  ,.body= "body"
  ,.upgrade= "proto"
  ,.content_length= 4
  ,.num_headers= 3
  ,.headers=
    { { "Connection", "upgrade" }
    , { "Upgrade", "h2c" }
    , { "Content-Length", "4" }
    }
  }

#define HTTP_101_RESPONSE_WITH_UPGRADE_HEADER_AND_TRANSFER_ENCODING 25
, {.name= "HTTP 101 response with Upgrade and Transfer-Encoding header"
  ,.type= st(HttpHeader)::Type::Response
  ,.raw= "HTTP/1.1 101 Switching Protocols\r\n"
         "Connection: upgrade\r\n"
         "Upgrade: h2c\r\n"
         "Transfer-Encoding: chunked\r\n"
         "\r\n"
         "2\r\n"
         "bo\r\n"
         "2\r\n"
         "dy\r\n"
         "0\r\n"
         "\r\n"
         "proto"
  ,.should_keep_alive= TRUE
  ,.message_complete_on_eof= FALSE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 101
  ,.response_status= "Switching Protocols"
  ,.body= "body"
  ,.upgrade= "proto"
  ,.content_length= -1
  ,.num_headers= 3
  ,.headers=
    { { "Connection", "upgrade" }
    , { "Upgrade", "h2c" }
    , { "Transfer-Encoding", "chunked" }
    }
  ,.num_chunks_complete= 3
  ,.chunk_lengths= { 2, 2 }
  }

#define HTTP_200_RESPONSE_WITH_UPGRADE_HEADER 26
, {.name= "HTTP 200 response with Upgrade header"
  ,.type= st(HttpHeader)::Type::Response
  ,.raw= "HTTP/1.1 200 OK\r\n"
         "Connection: upgrade\r\n"
         "Upgrade: h2c\r\n"
         "\r\n"
         "body"
  ,.should_keep_alive= FALSE
  ,.message_complete_on_eof= TRUE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 200
  ,.response_status= "OK"
  ,.body= "body"
  ,.upgrade= NULL
  ,.content_length= -1
  ,.num_headers= 2
  ,.headers=
    { { "Connection", "upgrade" }
    , { "Upgrade", "h2c" }
    }
  }

#define HTTP_200_RESPONSE_WITH_UPGRADE_HEADER_AND_CONTENT_LENGTH 27
, {.name= "HTTP 200 response with Upgrade and Content-Length header"
  ,.type= st(HttpHeader)::Type::Response
  ,.raw= "HTTP/1.1 200 OK\r\n"
         "Connection: upgrade\r\n"
         "Upgrade: h2c\r\n"
         "Content-Length: 4\r\n"
         "\r\n"
         "body"
  ,.should_keep_alive= TRUE
  ,.message_complete_on_eof= FALSE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 200
  ,.response_status= "OK"
  ,.content_length= 4
  ,.num_headers= 3
  ,.body= "body"
  ,.upgrade= NULL
  ,.headers=
    { { "Connection", "upgrade" }
    , { "Upgrade", "h2c" }
    , { "Content-Length", "4" }
    }
  }

#define HTTP_200_RESPONSE_WITH_UPGRADE_HEADER_AND_TRANSFER_ENCODING 28
, {.name= "HTTP 200 response with Upgrade and Transfer-Encoding header"
  ,.type= st(HttpHeader)::Type::Response
  ,.raw= "HTTP/1.1 200 OK\r\n"
         "Connection: upgrade\r\n"
         "Upgrade: h2c\r\n"
         "Transfer-Encoding: chunked\r\n"
         "\r\n"
         "2\r\n"
         "bo\r\n"
         "2\r\n"
         "dy\r\n"
         "0\r\n"
         "\r\n"
  ,.should_keep_alive= TRUE
  ,.message_complete_on_eof= FALSE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 200
  ,.response_status= "OK"
  ,.content_length= -1
  ,.num_headers= 3
  ,.body= "body"
  ,.upgrade= NULL
  ,.headers=
    { { "Connection", "upgrade" }
    , { "Upgrade", "h2c" }
    , { "Transfer-Encoding", "chunked" }
    }
  ,.num_chunks_complete= 3
  ,.chunk_lengths= { 2, 2 }
  }
#define HTTP_200_MULTI_TE_NOT_LAST_CHUNKED 29
, {.name= "HTTP 200 response with `chunked` being *not last* Transfer-Encoding"
  ,.type= st(HttpHeader)::Type::Response
  ,.raw= "HTTP/1.1 200 OK\r\n"
         "Transfer-Encoding: chunked, identity\r\n"
         "\r\n"
         "2\r\n"
         "OK\r\n"
         "0\r\n"
         "\r\n"
  ,.should_keep_alive= FALSE
  ,.message_complete_on_eof= TRUE
  ,.http_major= 1
  ,.http_minor= 1
  ,.status_code= 200
  ,.response_status= "OK"
  ,.content_length= -1
  ,.num_headers= 1
  ,.headers= { { "Transfer-Encoding", "chunked, identity" }
             }
  ,.body= "2\r\nOK\r\n0\r\n\r\n"
  ,.num_chunks_complete= 0
  }
};
}

int main() {
    //struct message requests
    int size = sizeof(responses)/sizeof(struct message);

    for(int i = 0;i<size;i++) {
        printf("////HttpPacketParser start %d ////\n",i);

        HttpPacketParser parser = createHttpPacketParser();
        struct message msg = responses[i];
        printf("%s\n",msg.raw);

        parser->pushHttpData(createByteArray((const byte *)msg.raw,strlen(msg.raw)));
        ArrayList<HttpPacket> packets = parser->doParse();
        //check size
        if(packets->size() != 1) {
            printf("HttpPacketParse CheckSize failed,packet size is %d \n",packets->size());
            continue;
        }

        HttpPacket packet = packets->get(0);
        HttpEntity entity = packet->getEntity();
        HttpHeader header = packet->getHeader();

        //check Type
        if(header->getType() != msg.type) {
            printf("HttpPacketParse CheckType failed,msg.type is %d,parse result is %d \n",msg.type,header->getType());
            continue;
        }

        //check status
        if(header->getResponseStatus() != msg.status_code) {
            printf("HttpPacketParse CheckStatus failed,msg.status is %d,parse result is %d \n",msg.status_code,header->getResponseStatus());
            continue;
        }

        //check response status
        if(strlen(msg.response_status) > 0) {
            String response_str = header->getResponseReason();
            if(response_str == nullptr || !response_str->equals(msg.response_status)) {
                printf("HttpPacketParse CheckResponseStatus failed,msg.response_status is %s,parse result is %s \n",msg.response_status,response_str->toChars());
                continue;
            }
        }

        //check body
        if(strlen(msg.body) > 0) {
            String content = entity->getContent()->toString();
            if(content == nullptr || !content->equals(msg.body)) {
                printf("HttpPacketParse CheckBody failed,msg.body is %s,parse result is %s \n",msg.body,content->toChars());
                continue;
            }
        }

        //check headers
        int num_headers = msg.num_headers;
        if(header->size() != num_headers) {
            //check link size
            if(header->getMethod() == st(HttpMethod)::Link) {
              if(header->getLink()->size() != num_headers) {
                  printf("HttpPacketParse CheckHeaderSize failed,msg.num_headers is %d,header size is %d \n",msg.num_headers,header->size());
                  continue;
              }
            }

        }

        for(int i = 0;i<num_headers;i++) {
            char *key = msg.headers[i][0];
            char *value = msg.headers[i][1];
            String fValue = packet->getHeader()->getValue(createString(key)->toLowerCase());
            if(fValue == nullptr) {
                printf("HttpPacketParser CheckHeader Fail,packet value is null,key is %s \n",key);
                continue;
            }

            if(!fValue->equals(value)) {
                printf("HttpPacketParser CheckHeader Fail,msg.key is %s,msg.value is %s,parse value is %s \n",
                                                          key,value,fValue->toChars());
                continue;
            }
        }

        //TODO:check chunk

        //check key_value
        if(msg.key_value_size > 0) {
            ArrayList<KeyValuePair<String,String>> list = entity->getEncodedKeyValues();
            if(list == nullptr) {
                printf("HttpPacketParser CheckKeyValue,parse EncodedKeyValues size is 0\n");
                continue;
            }

            int count = 0;
            for(int i = 0;i < msg.key_value_size;i++) {
                const char *key = msg.key_value[i];
                i++;
                const char *value = msg.key_value[i];

                KeyValuePair<String,String> pair = list->get(count);
                if(!pair->getKey()->equals(key) || !pair->getValue()->equals(value)) {
                    printf("HttpPacketParser CheckKeyValue Fail,parsed key is %s,key is %s,parser value is %s,value is %s\n",
                                pair->getKey()->toChars(),key,pair->getValue()->toChars(),value);
                }
                count++;
            }
        }


        //check upgrade
        if(msg.upgrade != nullptr && strlen(msg.upgrade) > 0) {
            String upgrade = entity->getUpgrade();
            if(upgrade == nullptr || !upgrade->equals(msg.upgrade)) {
              printf("HttpPacketParse CheckUpgrade failed,msg.upgrade is %s,parse result is %s \n",msg.upgrade,upgrade->toChars());
              continue;
            }
        }

        //check http major version
        HttpVersion ver = header->getVersion();
        if(ver == nullptr) {
            printf("HttpPacketParse CheckVersion failed,version is null \n");
            continue;
        }

        if(ver->getMajorVer() != msg.http_major) {
           printf("HttpPacketParse CheckMajorVersion failed,Msg.http_major is %d,parse major version is %d \n",msg.http_major,ver->getMajorVer());
           continue;
        }

        if(ver->getMinorVer() != msg.http_minor) {
           printf("HttpPacketParse CheckMinorVersion failed,Msg.http_minor is %d,parse minor version is %d \n",msg.http_major,ver->getMajorVer());
           continue;
        }
    }

}
