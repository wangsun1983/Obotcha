#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "Math.hpp"
#include "HttpAccessControlRequestHeaders.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpAccessControlRequestHeaders c = createHttpAccessControlRequestHeaders();
    c->import("X-PINGOTHER, Content-Type");
    auto list = c->getHeaders();
    if(!list->get(0)->equals("X-PINGOTHER")) {
      printf("---[HttpAccessControlRequestHeaders test Parse case1] [FAILED]--- \n");
      break;
    }

    if(!list->get(1)->equals("Content-Type")) {
      printf("---[HttpAccessControlRequestHeaders test Parse case2] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    HttpAccessControlRequestHeaders c = createHttpAccessControlRequestHeaders();
    c->import("X-PINGOTHER");
    auto list = c->getHeaders();
    if(!list->get(0)->equals("X-PINGOTHER")) {
      printf("---[HttpAccessControlRequestHeaders test Parse case3] [FAILED]--- \n");
      break;
    }
    break;
  }
  printf("---[HttpAccessControlRequestHeaders test Parse case100] [OK]--- \n");

}
