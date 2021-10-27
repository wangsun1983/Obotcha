#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "HttpAccessControlRequestMethod.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpAccessControlRequestMethod c = createHttpAccessControlRequestMethod();
    c->import("POST");
    if(!c->toString()->equals("POST")) {
      printf("---[HttpAccessControlRequestMethod test toString case1] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpAccessControlRequestMethod test toString case100] [OK]--- \n");

}
