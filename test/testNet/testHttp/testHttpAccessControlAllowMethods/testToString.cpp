#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "HttpAccessControlAllowMethods.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpAccessControlAllowMethods c = createHttpAccessControlAllowMethods();
    c->import("POST, GET, OPTIONS");
    if(!c->toString()->equals("POST, GET, OPTIONS")) {
      printf("---[HttpAccessControlAllowMethods test toString case1] [FAILED]--- ,str is %s\n",c->toString()->toChars());
      break;
    }
    break;
  }

  printf("---[HttpAccessControlAllowMethods test toString case100] [OK]--- \n");

}
