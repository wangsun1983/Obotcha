#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderKeepAlive.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpHeaderKeepAlive keepAlive = createHttpHeaderKeepAlive();
    keepAlive->import("timeout=5, max=1000");
    if(!keepAlive->toString()->equals("timeout=5, max=1000")) {
      printf("---[HttpHeaderKeepAlive test toString case1] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    HttpHeaderKeepAlive keepAlive = createHttpHeaderKeepAlive();
    keepAlive->import("1000");
    if(!keepAlive->toString()->equals("timeout=1000")) {
      printf("---[HttpHeaderKeepAlive test toString case2] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    HttpHeaderKeepAlive keepAlive = createHttpHeaderKeepAlive();
    keepAlive->import("timeout=5");
    if(!keepAlive->toString()->equals("timeout=5")) {
      printf("---[HttpHeaderKeepAlive test toString case3] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    HttpHeaderKeepAlive keepAlive = createHttpHeaderKeepAlive();
    keepAlive->import("Max=5");
    if(!keepAlive->toString()->equals("max=5")) {
      printf("---[HttpHeaderKeepAlive test toString case4] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpHeaderKeepAlive test toString case100] [OK]--- \n");
}
