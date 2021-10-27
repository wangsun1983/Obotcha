#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "HttpAccessControlMaxAge.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpAccessControlMaxAge c = createHttpAccessControlMaxAge();
    c->import("600");
    if(!c->toString()->equals("600")) {
      printf("---[HttpAccessControlMaxAge test toString case1] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpAccessControlMaxAge test toString case100] [OK]--- \n");

}
