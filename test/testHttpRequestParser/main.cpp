#include <stdio.h>
#include <unistd.h>

#include "http_parser.h"

#include "HttpRequestParser.hpp"

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

  /* * R E Q U E S T S * */
  const struct message requests[] =
  #define CURL_GET 0
  { {.name= "curl get"
    ,.type= HTTP_REQUEST
    ,.raw= "GET /test HTTP/1.1\r\n"
           "User-Agent: curl/7.18.0 (i486-pc-linux-gnu) libcurl/7.18.0 OpenSSL/0.9.8g zlib/1.2.3.3 libidn/1.1\r\n"
           "Host: 0.0.0.0=5000\r\n"
           "Accept: */*\r\n"
           "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_GET
    ,.request_url= "/test"
    ,.num_headers= 3
    ,.headers=
      { { "User-Agent", "curl/7.18.0 (i486-pc-linux-gnu) libcurl/7.18.0 OpenSSL/0.9.8g zlib/1.2.3.3 libidn/1.1" }
      , { "Host", "0.0.0.0=5000" }
      , { "Accept", "*/*" }
      }
    ,.body= ""
    }

  #define FIREFOX_GET 1
  , {.name= "firefox get"
    ,.type= HTTP_REQUEST
    ,.raw= "GET /favicon.ico HTTP/1.1\r\n"
           "Host: 0.0.0.0=5000\r\n"
           "User-Agent: Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9) Gecko/2008061015 Firefox/3.0\r\n"
           "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
           "Accept-Language: en-us,en;q=0.5\r\n"
           "Accept-Encoding: gzip,deflate\r\n"
           "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n"
           "Keep-Alive: 300\r\n"
           "Connection: keep-alive\r\n"
           "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_GET
    ,.request_url= "/favicon.ico"
    ,.num_headers= 8
    ,.headers=
      { { "Host", "0.0.0.0=5000" }
      , { "User-Agent", "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9) Gecko/2008061015 Firefox/3.0" }
      , { "Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8" }
      , { "Accept-Language", "en-us,en;q=0.5" }
      , { "Accept-Encoding", "gzip,deflate" }
      , { "Accept-Charset", "ISO-8859-1,utf-8;q=0.7,*;q=0.7" }
      , { "Keep-Alive", "300" }
      , { "Connection", "keep-alive" }
      }
    ,.body= ""
    }

  #define DUMBFUCK 2
  , {.name= "dumbfuck"
    ,.type= HTTP_REQUEST
    ,.raw= "GET /dumbfuck HTTP/1.1\r\n"
           "aaaaaaaaaaaaa:++++++++++\r\n"
           "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_GET
    ,.request_url= "/dumbfuck"
    ,.num_headers= 1
    ,.headers=
      { { "aaaaaaaaaaaaa",  "++++++++++" }
      }
    ,.body= ""
    }

  #define FRAGMENT_IN_URI 3
  , {.name= "fragment in url"
    ,.type= HTTP_REQUEST
    ,.raw= "GET /forums/1/topics/2375?page=1#posts-17408 HTTP/1.1\r\n"
           "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_GET
    /* XXX request url does include fragment? */
    ,.request_url= "/forums/1/topics/2375?page=1#posts-17408"
    ,.num_headers= 0
    ,.body= ""
    }

  #define GET_NO_HEADERS_NO_BODY 4
  , {.name= "get no headers no body"
    ,.type= HTTP_REQUEST
    ,.raw= "GET /get_no_headers_no_body/world HTTP/1.1\r\n"
           "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE /* would need Connection: close */
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_GET
    ,.request_url= "/get_no_headers_no_body/world"
    ,.num_headers= 0
    ,.body= ""
    }

  #define GET_ONE_HEADER_NO_BODY 5
  , {.name= "get one header no body"
    ,.type= HTTP_REQUEST
    ,.raw= "GET /get_one_header_no_body HTTP/1.1\r\n"
           "Accept: */*\r\n"
           "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE /* would need Connection: close */
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_GET
    ,.request_url= "/get_one_header_no_body"
    ,.num_headers= 1
    ,.headers=
      { { "Accept" , "*/*" }
      }
    ,.body= ""
    }

    #define GET_FUNKY_CONTENT_LENGTH 6
    , {.name= "get funky content length body hello"
      ,.type= HTTP_REQUEST
      ,.raw= "GET /get_funky_content_length_body_hello HTTP/1.0\r\n"
             "conTENT-Length: 5\r\n"
             "\r\n"
             "HELLO"
      ,.should_keep_alive= FALSE
      ,.message_complete_on_eof= FALSE
      ,.http_major= 1
      ,.http_minor= 0
      ,.method= HTTP_GET
      ,.request_url= "/get_funky_content_length_body_hello"
      ,.num_headers= 1
      ,.headers=
        { { "conTENT-Length" , "5" }
        }
      ,.body= "HELLO"
      }

  #define POST_IDENTITY_BODY_WORLD 7
  , {.name= "post identity body world"
    ,.type= HTTP_REQUEST
    ,.raw= "POST /post_identity_body_world?q=search#hey HTTP/1.1\r\n"
           "Accept: */*\r\n"
           "Transfer-Encoding: identity\r\n"
           "Content-Length: 5\r\n"
           "\r\n"
           "World"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_POST
    ,.request_url= "/post_identity_body_world?q=search#hey"
    ,.num_headers= 3
    ,.headers=
      { { "Accept", "*/*" }
      , { "Transfer-Encoding", "identity" }
      , { "Content-Length", "5" }
      }
    ,.body= "World"
    }

  #define POST_CHUNKED_ALL_YOUR_BASE 8
  , {.name= "post - chunked body: all your base are belong to us"
    ,.type= HTTP_REQUEST
    ,.raw= "POST /post_chunked_all_your_base HTTP/1.1\r\n"
           "Transfer-Encoding: chunked\r\n"
           "\r\n"
           "1e\r\nall your base are belong to us\r\n"
           "0\r\n"
           "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_POST
    ,.request_url= "/post_chunked_all_your_base"
    ,.num_headers= 1
    ,.headers=
      { { "Transfer-Encoding" , "chunked" }
      }
    ,.body= "all your base are belong to us"
    ,.num_chunks= 1
    ,.num_chunks_complete= 2
    ,.chunk_lengths= { 0x1e }
    }

  #define TWO_CHUNKS_MULT_ZERO_END 9
  , {.name= "two chunks ; triple zero ending"
    ,.type= HTTP_REQUEST
    ,.raw= "POST /two_chunks_mult_zero_end HTTP/1.1\r\n"
           "Transfer-Encoding: chunked\r\n"
           "\r\n"
           "5\r\nhello\r\n"
           "6\r\n world\r\n"
           "000\r\n"
           "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_POST
    ,.request_url= "/two_chunks_mult_zero_end"
    ,.num_headers= 1
    ,.headers=
      { { "Transfer-Encoding", "chunked" }
      }
    ,.body= "hello world"
    ,.num_chunks= 2
    ,.num_chunks_complete= 3
    ,.chunk_lengths= { 5, 6 }
    }

  #define CHUNKED_W_TRAILING_HEADERS 10
  , {.name= "chunked with trailing headers. blech."
    ,.type= HTTP_REQUEST
    ,.raw= "POST /chunked_w_trailing_headers HTTP/1.1\r\n"
           "Transfer-Encoding: chunked\r\n"
           "\r\n"
           "5\r\nhello\r\n"
           "6\r\n world\r\n"
           "0\r\n"
           "Vary: *\r\n"
           "Content-Type: text/plain\r\n"
           "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_POST
    ,.request_url= "/chunked_w_trailing_headers"
    ,.num_headers= 3
    ,.headers=
      { { "Transfer-Encoding",  "chunked" }
      , { "Vary", "*" }
      , { "Content-Type", "text/plain" }
      }
    ,.body= "hello world"
    ,.num_chunks= 2
    ,.num_chunks_complete= 3
    ,.chunk_lengths= { 5, 6 }
    }

  #define CHUNKED_W_BULLSHIT_AFTER_LENGTH 11
  , {.name= "with bullshit after the length"
    ,.type= HTTP_REQUEST
    ,.raw= "POST /chunked_w_bullshit_after_length HTTP/1.1\r\n"
           "Transfer-Encoding: chunked\r\n"
           "\r\n"
           "5; ihatew3;whatthefuck=aretheseparametersfor\r\nhello\r\n"
           "6; blahblah; blah\r\n world\r\n"
           "0\r\n"
           "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_POST
    ,.request_url= "/chunked_w_bullshit_after_length"
    ,.num_headers= 1
    ,.headers=
      { { "Transfer-Encoding", "chunked" }
      }
    ,.body= "hello world"
    ,.num_chunks= 2
    ,.num_chunks_complete= 3
    ,.chunk_lengths= { 5, 6 }
    }

  #define WITH_QUOTES 12
  , {.name= "with quotes"
    ,.type= HTTP_REQUEST
    ,.raw= "GET /with_\"stupid\"_quotes?foo=\"bar\" HTTP/1.1\r\n\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_GET
    ,.request_url= "/with_\"stupid\"_quotes?foo=\"bar\""
    ,.num_headers= 0
    ,.headers= { }
    ,.body= ""
    }

  #define APACHEBENCH_GET 13
  /* The server receiving this request SHOULD NOT wait for EOF
   * to know that content-length == 0.
   * How to represent this in a unit test? message_complete_on_eof
   * Compare with NO_CONTENT_LENGTH_RESPONSE.
   */
  , {.name = "apachebench get"
    ,.type= HTTP_REQUEST
    ,.raw= "GET /test HTTP/1.0\r\n"
           "Host: 0.0.0.0:5000\r\n"
           "User-Agent: ApacheBench/2.3\r\n"
           "Accept: */*\r\n\r\n"
    ,.should_keep_alive= FALSE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 0
    ,.method= HTTP_GET
    ,.request_url= "/test"
    ,.num_headers= 3
    ,.headers= { { "Host", "0.0.0.0:5000" }
               , { "User-Agent", "ApacheBench/2.3" }
               , { "Accept", "*/*" }
               }
    ,.body= ""
    }

  #define QUERY_URL_WITH_QUESTION_MARK_GET 14
  /* Some clients include '?' characters in query strings.
   */
  , {.name = "query url with question mark"
    ,.type= HTTP_REQUEST
    ,.raw= "GET /test.cgi?foo=bar?baz HTTP/1.1\r\n\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_GET
    ,.request_url= "/test.cgi?foo=bar?baz"
    ,.num_headers= 0
    ,.headers= {}
    ,.body= ""
    }

  #define PREFIX_NEWLINE_GET 15
  /* Some clients, especially after a POST in a keep-alive connection,
   * will send an extra CRLF before the next request
   */
  , {.name = "newline prefix get"
    ,.type= HTTP_REQUEST
    ,.raw= "\r\nGET /test HTTP/1.1\r\n\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_GET
    ,.request_url= "/test"
    ,.num_headers= 0
    ,.headers= { }
    ,.body= ""
    }

  #define UPGRADE_REQUEST 16
  , {.name = "upgrade request"
    ,.type= HTTP_REQUEST
    ,.raw= "GET /demo HTTP/1.1\r\n"
           "Host: example.com\r\n"
           "Connection: Upgrade\r\n"
           "Sec-WebSocket-Key2: 12998 5 Y3 1  .P00\r\n"
           "Sec-WebSocket-Protocol: sample\r\n"
           "Upgrade: WebSocket\r\n"
           "Sec-WebSocket-Key1: 4 @1  46546xW%0l 1 5\r\n"
           "Origin: http://example.com\r\n"
           "\r\n"
           "Hot diggity dogg"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_GET
    ,.request_url= "/demo"
    ,.num_headers= 7
    ,.upgrade="Hot diggity dogg"
    ,.headers= { { "Host", "example.com" }
               , { "Connection", "Upgrade" }
               , { "Sec-WebSocket-Key2", "12998 5 Y3 1  .P00" }
               , { "Sec-WebSocket-Protocol", "sample" }
               , { "Upgrade", "WebSocket" }
               , { "Sec-WebSocket-Key1", "4 @1  46546xW%0l 1 5" }
               , { "Origin", "http://example.com" }
               }
    ,.body= ""
    }

  #define CONNECT_REQUEST 17
  , {.name = "connect request"
    ,.type= HTTP_REQUEST
    ,.raw= "CONNECT 0-home0.netscape.com:443 HTTP/1.0\r\n"
           "User-agent: Mozilla/1.1N\r\n"
           "Proxy-authorization: basic aGVsbG86d29ybGQ=\r\n"
           "\r\n"
           "some data\r\n"
           "and yet even more data"
    ,.should_keep_alive= FALSE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 0
    ,.method= HTTP_CONNECT
    ,.request_url= "0-home0.netscape.com:443"
    ,.num_headers= 2
    ,.upgrade="some data\r\nand yet even more data"
    ,.headers= { { "User-agent", "Mozilla/1.1N" }
               , { "Proxy-authorization", "basic aGVsbG86d29ybGQ=" }
               }
    ,.body= ""
    }

  #define REPORT_REQ 18
  , {.name= "report request"
    ,.type= HTTP_REQUEST
    ,.raw= "REPORT /test HTTP/1.1\r\n"
           "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_REPORT
    ,.request_url= "/test"
    ,.num_headers= 0
    ,.headers= {}
    ,.body= ""
    }

  #define NO_HTTP_VERSION 19
  , {.name= "request with no http version"
    ,.type= HTTP_REQUEST
    ,.raw= "GET /\r\n"
           "\r\n"
    ,.should_keep_alive= FALSE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 0
    ,.http_minor= 9
    ,.method= HTTP_GET
    ,.request_url= "/"
    ,.num_headers= 0
    ,.headers= {}
    ,.body= ""
    }

  #define MSEARCH_REQ 20
  , {.name= "m-search request"
    ,.type= HTTP_REQUEST
    ,.raw= "M-SEARCH * HTTP/1.1\r\n"
           "HOST: 239.255.255.250:1900\r\n"
           "MAN: \"ssdp:discover\"\r\n"
           "ST: \"ssdp:all\"\r\n"
           "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_MSEARCH
    ,.request_url= "*"
    ,.num_headers= 3
    ,.headers= { { "HOST", "239.255.255.250:1900" }
               , { "MAN", "\"ssdp:discover\"" }
               , { "ST", "\"ssdp:all\"" }
               }
    ,.body= ""
    }

  #define LINE_FOLDING_IN_HEADER 20
  , {.name= "line folding in header value"
    ,.type= HTTP_REQUEST
    ,.raw= "GET / HTTP/1.1\r\n"
           "Line1:   abc\r\n"
           "\tdef\r\n"
           " ghi\r\n"
           "\t\tjkl\r\n"
           "  mno \r\n"
           "\t \tqrs\r\n"
           "Line2: \t line2\t\r\n"
           "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_GET
    ,.request_url= "/"
    ,.num_headers= 2
    ,.headers= { { "Line1", "abc def ghi jkl mno  qrs" }
               , { "Line2", "line2\t" }
               }
    ,.body= ""
    }


  #define QUERY_TERMINATED_HOST 21
  , {.name= "host terminated by a query string"
    ,.type= HTTP_REQUEST
    ,.raw= "GET http://hypnotoad.org?hail=all HTTP/1.1\r\n"
           "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_GET
    ,.request_url= "http://hypnotoad.org?hail=all"
    ,.num_headers= 0
    ,.headers= { }
    ,.body= ""
    }

  #define QUERY_TERMINATED_HOSTPORT 22
  , {.name= "host:port terminated by a query string"
    ,.type= HTTP_REQUEST
    ,.raw= "GET http://hypnotoad.org:1234?hail=all HTTP/1.1\r\n"
           "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_GET
    ,.request_url= "http://hypnotoad.org:1234?hail=all"
    ,.num_headers= 0
    ,.headers= { }
    ,.body= ""
    }

  #define SPACE_TERMINATED_HOSTPORT 23
  , {.name= "host:port terminated by a space"
    ,.type= HTTP_REQUEST
    ,.raw= "GET http://hypnotoad.org:1234 HTTP/1.1\r\n"
           "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_GET
    ,.request_url= "http://hypnotoad.org:1234"
    ,.num_headers= 0
    ,.headers= { }
    ,.body= ""
    }

  #if !HTTP_PARSER_STRICT
  #define UTF8_PATH_REQ 24
  , {.name= "utf-8 path request"
    ,.type= HTTP_REQUEST
    ,.raw= "GET /δ¶/δt/pope?q=1#narf HTTP/1.1\r\n"
           "Host: github.com\r\n"
           "\r\n"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_GET
    ,.request_url= "/δ¶/δt/pope?q=1#narf"
    ,.num_headers= 1
    ,.headers= { {"Host", "github.com" }
               }
    ,.body= ""
    }

  #define HOSTNAME_UNDERSCORE 25
  , {.name = "hostname underscore"
    ,.type= HTTP_REQUEST
    ,.raw= "CONNECT home_0.netscape.com:443 HTTP/1.0\r\n"
           "User-agent: Mozilla/1.1N\r\n"
           "Proxy-authorization: basic aGVsbG86d29ybGQ=\r\n"
           "\r\n"
    ,.should_keep_alive= FALSE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 0
    ,.method= HTTP_CONNECT
    ,.request_url= "home_0.netscape.com:443"
    ,.num_headers= 2
    ,.upgrade=""
    ,.headers= { { "User-agent", "Mozilla/1.1N" }
               , { "Proxy-authorization", "basic aGVsbG86d29ybGQ=" }
               }
    ,.body= ""
    }
  #endif  /* !HTTP_PARSER_STRICT */

  #define PATCH_REQ 26
  , {.name = "PATCH request"
    ,.type= HTTP_REQUEST
    ,.raw= "PATCH /file.txt HTTP/1.1\r\n"
           "Host: www.example.com\r\n"
           "Content-Type: application/example\r\n"
           "If-Match: \"e0023aa4e\"\r\n"
           "Content-Length: 10\r\n"
           "\r\n"
           "cccccccccc"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_PATCH
    ,.request_url= "/file.txt"
    ,.num_headers= 4
    ,.headers= { { "Host", "www.example.com" }
               , { "Content-Type", "application/example" }
               , { "If-Match", "\"e0023aa4e\"" }
               , { "Content-Length", "10" }
               }
    ,.body= "cccccccccc"
    }

  #define CONNECT_CAPS_REQUEST 27
  , {.name = "connect caps request"
    ,.type= HTTP_REQUEST
    ,.raw= "CONNECT HOME0.NETSCAPE.COM:443 HTTP/1.0\r\n"
           "User-agent: Mozilla/1.1N\r\n"
           "Proxy-authorization: basic aGVsbG86d29ybGQ=\r\n"
           "\r\n"
    ,.should_keep_alive= FALSE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 0
    ,.method= HTTP_CONNECT
    ,.request_url= "HOME0.NETSCAPE.COM:443"
    ,.num_headers= 2
    ,.upgrade=""
    ,.headers= { { "User-agent", "Mozilla/1.1N" }
               , { "Proxy-authorization", "basic aGVsbG86d29ybGQ=" }
               }
    ,.body= ""
    }

  #define IPV6_LITERAL_URI_GET 28
  , {.name = "IPv6 literal URI GET"
    ,.type= HTTP_REQUEST
    ,.raw= "GET http://[2a03:2880:2050:1f01:face:b00c:0:9]/ HTTP/1.0\r\n"
           "\r\n"
    ,.should_keep_alive= FALSE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 0
    ,.method= HTTP_GET
    ,.request_url= "http://[2a03:2880:2050:1f01:face:b00c:0:9]/"
    ,.num_headers= 0
    ,.headers= {}
    ,.body= ""
    }

  #define IPV6_LITERAL_URI_CONNECT 29
  , {.name = "IPv6 literal URI CONNECT"
    ,.type= HTTP_REQUEST
    ,.raw= "CONNECT [2a03:2880:2050:1f01:face:b00c:0:9]:443 HTTP/1.0\r\n"
           "\r\n"
    ,.should_keep_alive= FALSE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 0
    ,.method= HTTP_CONNECT
    ,.request_url= "[2a03:2880:2050:1f01:face:b00c:0:9]:443"
    ,.num_headers= 0
    ,.upgrade=""
    ,.headers= {}
    ,.body= ""
    }

  #define UPGRADE_POST_REQUEST 30
  , {.name = "upgrade post request"
    ,.type= HTTP_REQUEST
    ,.raw= "POST /demo HTTP/1.1\r\n"
           "Host: example.com\r\n"
           "Connection: Upgrade\r\n"
           "Upgrade: HTTP/2.0\r\n"
           "Content-Length: 15\r\n"
           "\r\n"
           "sweet post body"
           "Hot diggity dogg"
    ,.should_keep_alive= TRUE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 1
    ,.method= HTTP_POST
    ,.request_url= "/demo"
    ,.num_headers= 4
    ,.upgrade="Hot diggity dogg"
    ,.headers= { { "Host", "example.com" }
               , { "Connection", "Upgrade" }
               , { "Upgrade", "HTTP/2.0" }
               , { "Content-Length", "15" }
               }
    ,.body= "sweet post body"
    }

  #define CONNECT_WITH_BODY_REQUEST 31
  , {.name = "connect with body request"
    ,.type= HTTP_REQUEST
    ,.raw= "CONNECT foo.bar.com:443 HTTP/1.0\r\n"
           "User-agent: Mozilla/1.1N\r\n"
           "Proxy-authorization: basic aGVsbG86d29ybGQ=\r\n"
           "Content-Length: 10\r\n"
           "\r\n"
           "blarfcicle"
    ,.should_keep_alive= FALSE
    ,.message_complete_on_eof= FALSE
    ,.http_major= 1
    ,.http_minor= 0
    ,.method= HTTP_CONNECT
    ,.request_url= "foo.bar.com:443"
    ,.num_headers= 3
    ,.upgrade="blarfcicle"
    ,.headers= { { "User-agent", "Mozilla/1.1N" }
               , { "Proxy-authorization", "basic aGVsbG86d29ybGQ=" }
               , { "Content-Length", "10" }
               }
    ,.body= ""
    }

  //, {.name= NULL } /* sentinel */
  };

}

int main() {
    //struct message requests
    int size = sizeof(requests)/sizeof(struct message);
    printf("size is %d \n",size);

    for(int i = 0;i<size;i++) {
      printf("////HttpRequestParser start %d ////\n",i);
      HttpRequestParser parser = createHttpRequestParser();
      struct message msg = requests[i];
      parser->pushHttpData(createByteArray((const byte *)msg.raw,strlen(msg.raw)));
      ArrayList<HttpPacket> packets = parser->doParse();
      if(packets->size() != 1) {
        printf("HttpRequestParser Test1 Fail,index is %d,content is %s,size is %d \n",i,msg.raw,packets->size());
        continue;
      }
      printf("trace1 \n");
      //check method
      HttpPacket packet = packets->get(0);
      if(packet->getMethod() != msg.method) {
        printf("HttpRequestParser Test2 Fail,index is %d,pcket methods is %d,msg type is %d,\n content is %s \n",i,packet->getMethod(),msg.method,msg.raw);
        continue;
      }

      //check url
      if(!packet->getHeader()->getUrl()->equals(msg.request_url)) {
        printf("HttpRequestParser Test3 Fail,packet url is %s,msg url is %s \n",packet->getHeader()->getUrl()->toChars(),msg.request_url);
        continue;
      }
      printf("trace2 \n");
      //check header
      int headersize = msg.num_headers;
      for(int i = 0;i<headersize;i++) {
        char *key = msg.headers[i][0];
        char *value = msg.headers[i][1];
        String fValue = packet->getHeader()->getValue(createString(key)->toLowerCase());
        if(fValue == nullptr) {
          printf("HttpRequestParser Test4 Fail,packet value is null,key is %s \n",key);
          continue;
        }

        if(!fValue->equals(value)) {
          printf("HttpRequestParser Test5 Fail,packet value is %s,msg value is %s \n",fValue->toChars(),value);
          continue;
        }
      }
      printf("trace3 \n");
      //check Version
      HttpVersion version = packet->getVersion();
      if(version->getMajorVer() != msg.http_major || version->getMinorVer() != msg.http_minor) {
        printf("HttpRequestParser Test6 Fail,packet version is %d.%d,msg version is %d.%d \n",
                version->getMajorVer(),version->getMinorVer(),msg.http_major,msg.http_minor);
        continue;
      }
      printf("trace4 \n");
      //check content
      HttpEntity entity = packet->getEntity();
      if(strlen(msg.body) > 0) {
        printf("trace4_1 \n");
        if(entity == nullptr) {
          printf("HttpRequestParser Test6 Fail,packet entity is null\n");
          continue;
        }
        String content = entity->getContent()->toString();
        printf("trace4_2 \n");
        if(content == nullptr) {
          printf("HttpRequestParser Test7 Fail,packet content is null\n");
        } else if(!content->equals(msg.body)) {
          printf("HttpRequestParser Test8 Fail,packet content is %s,size is %d 111\n",content->toChars(),content->size());
          printf("HttpRequestParser Test8 Fail,packet content is %s,size is %d 222\n",msg.body,strlen(msg.body));
          int index = 0;
          for(;index < content->size();index++) {
            printf("[%d] is %x \n",index,content->toChars()[index]);
          }
          //for(;index < strlen(msg.body);index++) {
            //if(content->toChars()[index] != msg.body[index]) {
          //    printf("not equal at %d,v1 is %c,v2 is %c \n",index,content->toChars()[index],msg.body[index]);
            //}
          //}

          //printf("content->toChars()[%d] is %x \n",index,content->toChars()[index]);
        }
        printf("trace4_3 \n");
      } else {
        if(entity != nullptr && entity->getContent() != nullptr) {
          printf("HttpRequestParser Test9 Fail,packet content is %s\n",entity->getContent()->toString()->toChars());
        }
      }
    }
    printf("trace5 \n");

}
