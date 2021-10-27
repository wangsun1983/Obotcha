#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "Math.hpp"
#include "HttpAccessControlAllowCredentials.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpAccessControlAllowCredentials c = createHttpAccessControlAllowCredentials();
    c->import("true");
    if(!c->isAllowed()) {
      printf("---[HttpAccessControlAllowCredentials test Parse case1] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    HttpAccessControlAllowCredentials c = createHttpAccessControlAllowCredentials();
    c->import("false");
    if(c->isAllowed()) {
      printf("---[HttpAccessControlAllowCredentials test Parse case2] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpAccessControlAllowCredentials test Parse case100] [OK]--- \n");

}
