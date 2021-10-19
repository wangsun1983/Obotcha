#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "Math.hpp"
#include "HttpAccessControlMaxAge.hpp"
#include "HttpMethod.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpAccessControlMaxAge c = createHttpAccessControlMaxAge();
    c->import("600");
    if(c->get() != 600) {
      printf("---[HttpAccessControlMaxAge test Parse case1] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpAccessControlMaxAge test Parse case100] [OK]--- \n");
}
