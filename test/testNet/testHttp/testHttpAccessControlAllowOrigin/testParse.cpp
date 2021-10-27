#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "Math.hpp"
#include "HttpAccessControlAllowOrigin.hpp"
#include "HttpMethod.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpAccessControlAllowOrigin c = createHttpAccessControlAllowOrigin();
    c->import("https://developer.mozilla.org");
    if(!c->get()->equals("https://developer.mozilla.org")) {
      printf("---[HttpAccessControlAllowOrigin test Parse case1] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    HttpAccessControlAllowOrigin c = createHttpAccessControlAllowOrigin();
    c->import("*");
    if(!c->get()->equals("*")) {
      printf("---[HttpAccessControlAllowOrigin test Parse case2] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpAccessControlAllowOrigin test Parse case100] [OK]--- \n");

}
