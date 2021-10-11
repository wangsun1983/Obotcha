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
    if(link1->url == nullptr || !link1->url->equals("https://example.com")) {
      printf("---[HttpHeaderLink test Parse case1] [FAILED]--- link is %s\n",link1->url->toChars());
    }

    if(!link1->rel->equals("preload")) {
      printf("---[HttpHeaderLink test Parse case2] [FAILED]--- rel is %s\n",link1->rel->toChars());
    }
    break;
  }

  printf("---[HttpHeaderLink test Parse case100] [OK]--- \n");

}
