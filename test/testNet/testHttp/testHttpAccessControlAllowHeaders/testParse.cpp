#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "Math.hpp"
#include "HttpAccessControlAllowHeaders.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpAccessControlAllowHeaders c = createHttpAccessControlAllowHeaders();
    c->import("X-Custom-Header, Upgrade-Insecure-Requests");
    auto list = c->getHeaders();
    if(!list->get(0)->equals("X-Custom-Header")) {
      printf("---[HttpAccessControlAllowHeaders test Parse case1] [FAILED]--- \n");
      break;
    }

    if(!list->get(1)->equals("Upgrade-Insecure-Requests")) {
      printf("---[HttpAccessControlAllowHeaders test Parse case2] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    HttpAccessControlAllowHeaders c = createHttpAccessControlAllowHeaders();
    c->import("*");
    auto list = c->getHeaders();
    if(!list->get(0)->equals("*")) {
      printf("---[HttpAccessControlAllowHeaders test Parse case3] [FAILED]--- \n");
      break;
    }

    break;
  }
  printf("---[HttpAccessControlAllowCredentials test Parse case100] [OK]--- \n");

}
