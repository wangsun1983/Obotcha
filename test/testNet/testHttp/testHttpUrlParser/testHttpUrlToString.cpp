#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderParser.hpp"
#include "ByteRingArrayReader.hpp"
#include "HttpMethod.hpp"

using namespace obotcha;

void testHttpUrlToString() {
  while(1) {
    const char *raw= "/demo";
    HttpUrl url = createHttpUrl(raw);
    if(!url->toString()->equals("/demo")) {
      printf("---[HttpUrlToString test case1_1] [FAILED]--- \n");
    }
    break;
  }

  while(1) {
    String request =  "http://su:abc@localhost:1234/test.cgi?a=b&c=d#fffsss";
    HttpUrl url = createHttpUrl(request);
    if(!url->toString()->equals("http://su:abc@localhost:1234/test.cgi?a=b&c=d#fffsss")) {
      printf("---[HttpUrlToString test case2] [FAILED]--- url is %s\n",url->toString()->toChars());
    }
    break;
  }

  while(1) {
    String request =  "http://abdd@localhost/test.cgi?a=b&c=d";
    HttpUrl url = createHttpUrl(request);
    if(!url->toString()->equals("http://abdd@localhost/test.cgi?a=b&c=d")) {
      printf("---[HttpUrlToString test case3] [FAILED]--- \n");
    }
    break;
  }

  while(1) {
    HttpUrl url =  createHttpUrl("https://su:abc@localhost/test/wangsl/01234");
    if(!url->toString()->equals("https://su:abc@localhost/test/wangsl/01234")) {
      printf("---[HttpUrlToString test case4] [FAILED]--- \n");
    }
    break;
  }

  while(1) {
    HttpUrl url =  createHttpUrl("https://ssaabb/test/wangsl/01234");
    if(!url->toString()->equals("https://ssaabb/test/wangsl/01234")) {
      printf("---[HttpUrlToString test case5] [FAILED]--- \n");
    }
    break;
  }

  while(1) {
    HttpUrl url =  createHttpUrl("https://ssaabb:123");
    if(!url->toString()->equals("https://ssaabb:123")) {
      printf("---[HttpUrlToString test case6] [FAILED]--- \n");
    }
    break;
  }

  while(1) {
    HttpUrl url =  createHttpUrl("su:abc@localhost:1234/test.cgi?a=b&c=d#fffsss");
    if(!url->toString()->equals("su:abc@localhost:1234/test.cgi?a=b&c=d#fffsss")) {
      printf("---[HttpUrlToString test case7] [FAILED]---,url is %s \n",url->toString()->toChars());
    }
    break;
  }

  while(1) {
    HttpUrl url =  createHttpUrl("https://ssaabb:123#frag");
    if(!url->toString()->equals("https://ssaabb:123#frag")) {
      printf("---[HttpUrlToString test case8] [FAILED]--- ,url is %s\n",url->toString()->toChars());
    }
    break;
  }

  printf("---[HttpUrlToString test case100] [OK]--- \n");

}
