#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "Math.hpp"
#include "HttpAllow.hpp"
#include "HttpMethod.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpAllow c = createHttpAllow();
    c->import("POST, GET, OPTIONS");
    auto list = c->getMethods();
    if(list->get(0)->toValue() != st(HttpMethod)::Post) {
      printf("---[HttpAllow test Parse case1] [FAILED]--- \n");
      break;
    }

    if(list->get(1)->toValue() != st(HttpMethod)::Get) {
      printf("---[HttpAllow test Parse case2] [FAILED]--- \n");
      break;
    }

    if(list->get(2)->toValue() != st(HttpMethod)::Options) {
      printf("---[HttpAllow test Parse case3] [FAILED]--- \n");
      break;
    }
    break;
  }


  printf("---[HttpAllow test Parse case100] [OK]--- \n");

}
