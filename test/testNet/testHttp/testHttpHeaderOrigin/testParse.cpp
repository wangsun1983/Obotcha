#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderOrigin.hpp"
#include "Math.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpHeaderOrigin match = createHttpHeaderOrigin();
    match->import("");
    HttpUrl url = match->get();
    if(url == nullptr){
      printf("---[HttpHeaderOrigin test parse case1] [FAILED]--- \n");
      break;
    }

    break;
  }

  while(1) {
    HttpHeaderOrigin match = createHttpHeaderOrigin();
    match->import("https://developer.mozilla.org:1234");
    HttpUrl url = match->get();
    if(url == nullptr){
      printf("---[HttpHeaderOrigin test parse case2] [FAILED]--- \n");
      break;
    }

    if(!url->getScheme()->equals("https")) {
      printf("---[HttpHeaderOrigin test parse case3] [FAILED]--- \n");
      break;
    }

    if(!url->getHost()->equals("developer.mozilla.org")) {
      printf("---[HttpHeaderOrigin test parse case4] [FAILED]--- \n");
      break;
    }

    if(url->getPort() != 1234) {
      printf("---[HttpHeaderOrigin test parse case5] [FAILED]--- \n");
      break;
    }

    break;
  }
  printf("---[HttpHeaderOrigin test Parse case100] [OK]--- \n");
}
