#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderLink.hpp"

using namespace obotcha;

void testLinkToString() {
  while(1) {
    HttpHeaderLink link1 = createHttpHeaderLink("<https://example.com>; rel=\"preload\"");
    if(!link1->toString()->equals("<https://example.com>; rel=\"preload\"")) {
      printf("---[HttpHeaderLink test toString case1] [FAILED]--- link is %s\n",link1->toString()->toChars());
    }
    break;
  }

  printf("---[HttpHeaderLink test toString case100] [OK]--- \n");
}
