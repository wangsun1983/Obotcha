#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "Math.hpp"
#include "HttpAccessControlRequestMethod.hpp"
#include "HttpMethod.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpAccessControlRequestMethod c = createHttpAccessControlRequestMethod();
    c->import("POST");
    if(c->get() != st(HttpMethod)::Post){
      printf("---[HttpAccessControlRequestMethod test Parse case1] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpAccessControlRequestMethod test Parse case100] [OK]--- \n");

}
