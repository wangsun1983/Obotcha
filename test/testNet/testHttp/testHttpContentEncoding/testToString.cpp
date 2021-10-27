#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "HttpContentEncoding.hpp"
#include "HttpProtocol.hpp"
using namespace obotcha;

void testToString() {
  while(1) {
    HttpContentEncoding c = createHttpContentEncoding();
    c->import("gzip, deflate");
    if(!c->toString()->equals("gzip, deflate")) {
      printf("---[HttpClearSiteData test toString case1] [OK]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpClearSiteData test toString case100] [OK]--- \n");

}
