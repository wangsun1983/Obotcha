#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "HttpAccessControlAllowHeaders.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpAccessControlAllowHeaders c = createHttpAccessControlAllowHeaders();
    c->import("X-Custom-Header, Upgrade-Insecure-Requests");
    if(!c->toString()->equals("X-Custom-Header, Upgrade-Insecure-Requests")) {
      printf("---[HttpAccessControlAllowCredentials test toString case1] [FAILED]--- ,str is %s\n",c->toString()->toChars());
      break;
    }
    break;
  }

  while(1) {
    HttpAccessControlAllowHeaders c = createHttpAccessControlAllowHeaders();
    c->import("*");
    if(!c->toString()->equals("*")) {
      printf("---[HttpAccessControlAllowCredentials test toString case2] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpAccessControlAllowCredentials test toString case100] [OK]--- \n");

}
