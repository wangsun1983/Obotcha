#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderHost.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpHeaderHost digest = createHttpHeaderHost();
    digest->import(" developer.mozilla.org:1234");
    if(!digest->toString()->equals("developer.mozilla.org:1234")) {
      printf("---[HttpHeaderHost test toString case1] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    HttpHeaderHost digest = createHttpHeaderHost();
    digest->import(" developer.mozilla.org");
    if(!digest->toString()->equals("developer.mozilla.org")) {
      printf("---[HttpHeaderHost test toString case2] [FAILED]--- \n");
      break;
    }
    break;
  }
  printf("---[HttpHeaderHost test toString case100] [OK]--- \n");
}
