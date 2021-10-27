#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "HttpAccessControlExposeHeaders.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpAccessControlExposeHeaders c = createHttpAccessControlExposeHeaders();
    c->import("Content-Length, X-Kuma-Revision");
    if(c->toString()->equals("Content-Length, X-Kuma-Revision")) {
      printf("---[HttpAccessControlAllowOrigin test toString case1] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpAccessControlAllowOrigin test toString case100] [OK]--- \n");

}
