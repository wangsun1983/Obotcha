#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "Math.hpp"
#include "HttpAllow.hpp"
#include "HttpClearSiteData.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpClearSiteData c = createHttpClearSiteData();
    c->import("\"cache\", \"cookies\", \"storage\", \"executionContexts\"");
    if(c->isCache()) {
      printf("---[HttpClearSiteData test Parse case1] [FAILED]--- \n");
      break;
    }

    if(c->isCookies()) {
      printf("---[HttpClearSiteData test Parse case2] [FAILED]--- \n");
      break;
    }

    if(c->isStorage()) {
      printf("---[HttpClearSiteData test Parse case3] [FAILED]--- \n");
      break;
    }

    if(c->isExecutionContexts()) {
      printf("---[HttpClearSiteData test Parse case4] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpClearSiteData test Parse case100] [OK]--- \n");

}
