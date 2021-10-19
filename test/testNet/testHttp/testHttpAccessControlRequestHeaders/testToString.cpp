#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "HttpAccessControlRequestHeaders.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpAccessControlRequestHeaders c = createHttpAccessControlRequestHeaders();
    c->import("X-PINGOTHER, Content-Type");
    if(!c->toString()->equals("X-PINGOTHER, Content-Type")) {
      printf("---[HttpAccessControlRequestHeaders test toString case1] [FAILED]--- \n");
      break;
    }

    break;
  }

  while(1) {
    HttpAccessControlRequestHeaders c = createHttpAccessControlRequestHeaders();
    c->import("X-PINGOTHER");
    if(!c->toString()->equals("X-PINGOTHER")) {
      printf("---[HttpAccessControlRequestHeaders test toString case3] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpAccessControlRequestHeaders test toString case100] [OK]--- \n");

}
