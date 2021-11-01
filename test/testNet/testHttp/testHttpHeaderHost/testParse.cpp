#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderHost.hpp"
#include "Math.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpHeaderHost digest = createHttpHeaderHost();
    digest->import(" developer.mozilla.org:1234");
    auto host = digest->getHost();
    if(!host->equals("developer.mozilla.org")) {
      printf("---[HttpHeaderHost test Parse case1] [FAILED]--- host is%s\n",host->toChars());
      break;
    }

    if(digest->getPort() != 1234) {
      printf("---[HttpHeaderHost test Parse case2] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    HttpHeaderHost digest = createHttpHeaderHost();
    digest->import(" developer.mozilla.org");
    auto host = digest->getHost();
    if(!host->equals("developer.mozilla.org")) {
      printf("---[HttpHeaderHost test Parse case3] [FAILED]--- \n");
      break;
    }
    break;
  }


  printf("---[HttpHeaderHost test Parse case100] [OK]--- \n");
}
