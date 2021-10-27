#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "Math.hpp"
#include "HttpAge.hpp"
#include "HttpMethod.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpAge c = createHttpAge();
    c->import("600");
    if(c->get() != 600) {
      printf("---[HttpAge test Parse case1] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpAge test Parse case100] [OK]--- \n");
}
