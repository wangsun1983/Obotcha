#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "Math.hpp"
#include "HttpAllow.hpp"
#include "HttpContentEncoding.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpContentEncoding c = createHttpContentEncoding();
    c->import("gzip, deflate");
    auto list = c->get();
    if(!list->get(0)->equals("gzip")) {
      printf("---[HttpClearSiteData test Parse case1] [FAILED]--- \n");
      break;
    }

    if(!list->get(1)->equals("deflate")) {
      printf("---[HttpClearSiteData test Parse case2] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpClearSiteData test Parse case100] [OK]--- \n");

}
