#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "Math.hpp"
#include "HttpAccessControlAllowMethods.hpp"
#include "HttpMethod.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpAccessControlAllowMethods c = createHttpAccessControlAllowMethods();
    c->import("POST, GET, OPTIONS");
    auto list = c->getMethods();
    if(list->get(0)->toValue() != st(HttpMethod)::Post) {
      printf("---[HttpAccessControlAllowMethods test Parse case1] [FAILED]--- \n");
      break;
    }

    if(list->get(1)->toValue() != st(HttpMethod)::Get) {
      printf("---[HttpAccessControlAllowMethods test Parse case2] [FAILED]--- \n");
      break;
    }

    if(list->get(2)->toValue() != st(HttpMethod)::Options) {
      printf("---[HttpAccessControlAllowMethods test Parse case3] [FAILED]--- \n");
      break;
    }
    break;
  }


  printf("---[HttpAccessControlAllowMethods test Parse case100] [OK]--- \n");

}
