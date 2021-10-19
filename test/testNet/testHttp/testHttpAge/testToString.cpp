#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "HttpAge.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpAge c = createHttpAge();
    c->import("600");
    if(!c->toString()->equals("600")) {
      printf("---[HttpAge test toString case1] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpAge test toString case100] [OK]--- \n");

}
