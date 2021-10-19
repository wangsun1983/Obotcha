#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "HttpAccessControlAllowCredentials.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpAccessControlAllowCredentials c = createHttpAccessControlAllowCredentials();
    c->import("true");
    if(!c->toString()->equals("true")) {
      printf("---[HttpAccessControlAllowCredentials test toString case1] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    HttpAccessControlAllowCredentials c = createHttpAccessControlAllowCredentials();
    c->import("false");
    if(!c->toString()->equals("false")) {
      printf("---[HttpAccessControlAllowCredentials test toString case2] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpAccessControlAllowCredentials test Parse case100] [OK]--- \n");



  printf("---[HttpAccessControlAllowCredentials test toString case100] [OK]--- \n");

}
