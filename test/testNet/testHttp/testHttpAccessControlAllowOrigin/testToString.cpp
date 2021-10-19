#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "HttpAccessControlAllowOrigin.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpAccessControlAllowOrigin c = createHttpAccessControlAllowOrigin();
    c->import("https://developer.mozilla.org");
    if(!c->toString()->equals("https://developer.mozilla.org")) {
      printf("---[HttpAccessControlAllowOrigin test toString case1] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    HttpAccessControlAllowOrigin c = createHttpAccessControlAllowOrigin();
    c->import("*");
    if(!c->toString()->equals("*")) {
      printf("---[HttpAccessControlAllowOrigin test toString case2] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpAccessControlAllowOrigin test toString case100] [OK]--- \n");

}
