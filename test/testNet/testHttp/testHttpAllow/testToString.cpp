#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "HttpAllow.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpAllow c = createHttpAllow();
    c->import("POST, GET, OPTIONS");
    if(!c->toString()->equals("POST, GET, OPTIONS")) {
      printf("---[HttpAllow test toString case1] [FAILED]--- ,str is %s\n",c->toString()->toChars());
      break;
    }
    break;
  }

  printf("---[HttpAllow test toString case100] [OK]--- \n");

}
