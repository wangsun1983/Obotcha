#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "Math.hpp"
#include "HttpAccessControlExposeHeaders.hpp"
#include "HttpMethod.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpAccessControlExposeHeaders c = createHttpAccessControlExposeHeaders();
    c->import("Content-Length, X-Kuma-Revision");
    auto list = c->getHeaders();
    String v0 = list->get(0);
    if(!v0->equals("Content-Length")) {
      printf("---[HttpAccessControlExposeHeaders test Parse case1] [FAILED]--- \n");
      break;
    }

    String v1 = list->get(1);
    if(!v1->equals("X-Kuma-Revision")) {
      printf("---[HttpAccessControlExposeHeaders test Parse case2] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpAccessControlExposeHeaders test Parse case100] [OK]--- \n");

}
