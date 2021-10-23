#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "HttpClearSiteData.hpp"
#include "HttpProtocol.hpp"
using namespace obotcha;

void testToString() {
  while(1) {
    HttpClearSiteData c = createHttpClearSiteData();
    c->import("\"cache\", \"cookies\", \"storage\", \"executionContexts\"");

    HttpClearSiteData c2 = createHttpClearSiteData(c->toString());

    if(c->isCache() != c2->isCache()) {
      printf("---[HttpClearSiteData test toString case1] [FAILED]--- \n");
      break;
    }

    if(c->isCookies() != c2->isCookies()) {
      printf("---[HttpClearSiteData test toString case2] [FAILED]--- \n");
      break;
    }

    if(c->isStorage() != c2->isStorage()) {
      printf("---[HttpClearSiteData test toString case3] [FAILED]--- \n");
      break;
    }

    if(c->isExecutionContexts() != c2->isExecutionContexts()) {
      printf("---[HttpClearSiteData test toString case4] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpClearSiteData test toString case100] [OK]--- \n");

}
