#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderLink.hpp"

using namespace obotcha;

void testLinkParse() {
  while(1) {
    HttpHeaderLink link1 = createHttpHeaderLink("<https://example.com>; rel=\"preload\"");
    if(link1->getUrl() == nullptr || !link1->getUrl()->equals("https://example.com")) {
      printf("---[HttpHeaderLink test Parse case1] [FAILED]--- link is %s\n",link1->getUrl()->toChars());
    }

    if(!link1->getProp("rel")->equals("preload")) {
      printf("---[HttpHeaderLink test Parse case2] [FAILED]--- rel is %s\n",link1->getProp("rel")->toChars());
    }
    break;
  }

  printf("---[HttpHeaderLink test Parse case100] [OK]--- \n");

}
