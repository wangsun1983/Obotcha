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

void testHttpUrlParse() {
  while(1) {
    const char *raw= "/demo";
    HttpUrl url = createHttpUrl(raw);
    if(!url->getPath()->equals("demo")) {
        printf("---[HttpUrlParse test Parse case1] [FAILED]--- \n");
    }

    if(!url->toString()->equals("/demo")) {
      printf("---[HttpUrlParse test Parse case1_1] [FAILED]--- \n");
    }
    break;
  }

  while(1) {
    String request =  "http://su:abc@localhost:1234/test.cgi?a=b&c=d#fffsss";
    //HttpUrlParser parser = createHttpUrl(request);
    //HttpUrl url = parser->parseUrl(request);
    HttpUrl url = createHttpUrl(request);
    if(!url->getScheme()->equals("http")) {
      printf("---[HttpUrlParse test Parse case2] [FAILED]--- ,scheme is %s\n",url->getScheme()->toChars());
      break;
    }

    if(!url->getUser()->equals("su")) {
      printf("---[HttpUrlParse test Parse case3] [FAILED]--- \n");
      break;
    }

    if(!url->getHost()->equals("localhost")) {
      printf("---[HttpUrlParse test Parse case3_1] [FAILED]--- \n");
      break;
    }

    if(url->getPort() != 1234) {
      printf("---[HttpUrlParse test Parse case3_2] [FAILED]--- \n");
      break;
    }

    if(!url->getPassword()->equals("abc")) {
      printf("---[HttpUrlParse test Parse case4] [FAILED]--- \n");
      break;
    }

    if(!url->getPath()->equals("test.cgi")) {
      printf("---[HttpUrlParse test Parse case5] [FAILED]--- path is %s\n",url->getPath()->toChars());
      break;
    }

    if(!url->getFragment()->equals("fffsss")) {
      printf("---[HttpUrlParse test Parse case6] [FAILED]--- \n");
      break;
    }

    auto query = url->getQuery();
    auto list = query->getValues();
    auto p0 = list->get(0);
    if(!p0->getKey()->equals("a")) {
      printf("---[HttpUrlParse test Parse case7] [FAILED]--- \n");
      break;
    }

    if(!p0->getValue()->equals("b")) {
      printf("---[HttpUrlParse test Parse case8] [FAILED]--- \n");
      break;
    }

    auto p1 = list->get(1);
    if(!p1->getKey()->equals("c")) {
      printf("---[HttpUrlParse test Parse case9] [FAILED]--- \n");
      break;
    }

    if(!p1->getValue()->equals("d")) {
      printf("---[HttpUrlParse test Parse case10] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    String request =  "http://abdd@localhost/test.cgi?a=b&c=d";
    HttpUrl url = createHttpUrl(request);
    if(!url->getScheme()->equals("http")) {
      printf("---[HttpUrlParse test Parse case11] [FAILED]--- ,scheme is %s\n",url->getScheme()->toChars());
      break;
    }

    if(!url->getUser()->equals("abdd")) {
      printf("---[HttpUrlParse test Parse case12] [FAILED]--- \n");
      break;
    }

    if(!url->getHost()->equals("localhost")) {
      printf("---[HttpUrlParse test Parse case13] [FAILED]--- \n");
      break;
    }

    if(url->getPort() != -1) {
      printf("---[HttpUrlParse test Parse case14] [FAILED]--- \n");
      break;
    }

    if(url->getPassword() != nullptr) {
      printf("---[HttpUrlParse test Parse case15] [FAILED]--- \n");
      break;
    }

    if(!url->getPath()->equals("test.cgi")) {
      printf("---[HttpUrlParse test Parse case16] [FAILED]--- path is %s\n",url->getPath()->toChars());
      break;
    }

    if(url->getFragment() != nullptr) {
      printf("---[HttpUrlParse test Parse case17] [FAILED]--- \n");
      break;
    }

    auto query = url->getQuery();
    auto list = query->getValues();
    auto p0 = list->get(0);
    if(!p0->getKey()->equals("a")) {
      printf("---[HttpUrlParse test Parse case18] [FAILED]--- \n");
      break;
    }

    if(!p0->getValue()->equals("b")) {
      printf("---[HttpUrlParse test Parse case19] [FAILED]--- \n");
      break;
    }

    auto p1 = list->get(1);
    if(!p1->getKey()->equals("c")) {
      printf("---[HttpUrlParse test Parse case20] [FAILED]--- \n");
      break;
    }

    if(!p1->getValue()->equals("d")) {
      printf("---[HttpUrlParse test Parse case21] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    HttpUrl url =  createHttpUrl("https://su:abc@localhost/test/wangsl/01234");
    if(!url->getScheme()->equals("https")) {
      printf("---[HttpUrlParse test Parse case22] [FAILED]--- ,scheme is %s\n",url->getScheme()->toChars());
      break;
    }

    if(!url->getUser()->equals("su")) {
      printf("---[HttpUrlParse test Parse case23] [FAILED]--- \n");
      break;
    }

    if(!url->getPassword()->equals("abc")) {
      printf("---[HttpUrlParse test Parse case24] [FAILED]--- \n");
      break;
    }

    if(!url->getHost()->equals("localhost")) {
      printf("---[HttpUrlParse test Parse case25] [FAILED]--- \n");
      break;
    }

    if(!url->getPath()->equals("test/wangsl/01234")) {
      printf("---[HttpUrlParse test Parse case26] [FAILED]--- path is %s\n",url->getPath()->toChars());
      break;
    }

    break;
  }

  while(1) {
    HttpUrl url =  createHttpUrl("https://ssaabb/test/wangsl/01234");
    if(!url->getScheme()->equals("https")) {
      printf("---[HttpUrlParse test Parse case27] [FAILED]--- ,scheme is %s\n",url->getScheme()->toChars());
      break;
    }

    if(url->getUser() != nullptr) {
      printf("---[HttpUrlParse test Parse case28] [FAILED]--- \n");
      break;
    }

    if(url->getPassword() != nullptr) {
      printf("---[HttpUrlParse test Parse case29] [FAILED]--- \n");
      break;
    }

    if(!url->getHost()->equals("ssaabb")) {
      printf("---[HttpUrlParse test Parse case30] [FAILED]--- \n");
      break;
    }

    if(!url->getPath()->equals("test/wangsl/01234")) {
      printf("---[HttpUrlParse test Parse case31] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    HttpUrl url =  createHttpUrl("https://ssaabb:123");
    if(!url->getScheme()->equals("https")) {
      printf("---[HttpUrlParse test Parse case32] [FAILED]--- ,scheme is %s\n",url->getScheme()->toChars());
      break;
    }

    if(url->getUser() != nullptr) {
      printf("---[HttpUrlParse test Parse case33] [FAILED]--- \n");
      break;
    }

    if(url->getPassword() != nullptr) {
      printf("---[HttpUrlParse test Parse case34] [FAILED]--- \n");
      break;
    }

    if(!url->getHost()->equals("ssaabb")) {
      printf("---[HttpUrlParse test Parse case35] [FAILED]--- \n");
      break;
    }

    if(url->getPort() != 123) {
      printf("---[HttpUrlParse test Parse case36] [FAILED]--- \n");
      break;
    }

    if(url->getPath() != nullptr) {
      printf("---[HttpUrlParse test Parse case37] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    String request =  "su:abc@localhost:1234/test.cgi?a=b&c=d#fffsss";
    //HttpUrlParser parser = createHttpUrl(request);
    //HttpUrl url = parser->parseUrl(request);
    HttpUrl url = createHttpUrl(request);
    if(url->getScheme() != nullptr) {
      printf("---[HttpUrlParse test Parse case38] [FAILED]--- ,scheme is %s\n",url->getScheme()->toChars());
      break;
    }

    if(!url->getUser()->equals("su")) {
      printf("---[HttpUrlParse test Parse case39] [FAILED]--- \n");
      break;
    }

    if(!url->getHost()->equals("localhost")) {
      printf("---[HttpUrlParse test Parse case40] [FAILED]--- \n");
      break;
    }

    if(url->getPort() != 1234) {
      printf("---[HttpUrlParse test Parse case41] [FAILED]--- \n");
      break;
    }

    if(!url->getPassword()->equals("abc")) {
      printf("---[HttpUrlParse test Parse case42] [FAILED]--- \n");
      break;
    }

    if(!url->getPath()->equals("test.cgi")) {
      printf("---[HttpUrlParse test Parse case43] [FAILED]--- path is %s\n",url->getPath()->toChars());
      break;
    }

    if(!url->getFragment()->equals("fffsss")) {
      printf("---[HttpUrlParse test Parse case44] [FAILED]--- \n");
      break;
    }

    auto query = url->getQuery();
    auto list = query->getValues();
    auto p0 = list->get(0);
    if(!p0->getKey()->equals("a")) {
      printf("---[HttpUrlParse test Parse case45] [FAILED]--- \n");
      break;
    }

    if(!p0->getValue()->equals("b")) {
      printf("---[HttpUrlParse test Parse case46] [FAILED]--- \n");
      break;
    }

    auto p1 = list->get(1);
    if(!p1->getKey()->equals("c")) {
      printf("---[HttpUrlParse test Parse case47] [FAILED]--- \n");
      break;
    }

    if(!p1->getValue()->equals("d")) {
      printf("---[HttpUrlParse test Parse case48] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    HttpUrl url =  createHttpUrl("https://ssaabb:123#frag");
    if(!url->getScheme()->equals("https")) {
      printf("---[HttpUrlParse test Parse case49] [FAILED]--- ,scheme is %s\n",url->getScheme()->toChars());
      break;
    }

    if(url->getUser() != nullptr) {
      printf("---[HttpUrlParse test Parse case50] [FAILED]--- \n");
      break;
    }

    if(url->getPassword() != nullptr) {
      printf("---[HttpUrlParse test Parse case51] [FAILED]--- \n");
      break;
    }

    if(!url->getHost()->equals("ssaabb")) {
      printf("---[HttpUrlParse test Parse case52] [FAILED]--- \n");
      break;
    }

    if(url->getPort() != 123) {
      printf("---[HttpUrlParse test Parse case53] [FAILED]--- \n");
      break;
    }

    if(url->getPath() != nullptr) {
      printf("---[HttpUrlParse test Parse case54] [FAILED]--- \n");
      break;
    }

    if(!url->getFragment()->equals("frag")) {
      printf("---[HttpUrlParse test Parse case55] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpUrlParse test Parse case100] [OK]--- \n");

}
