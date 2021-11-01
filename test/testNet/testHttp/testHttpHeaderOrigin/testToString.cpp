#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderOrigin.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpHeaderOrigin match = createHttpHeaderOrigin();
    match->import("");
    
    if(!match->toString()->equals("")){
      printf("---[HttpHeaderOrigin test toString case1] [FAILED]--- \n");
      break;
    }

    break;
  }

  while(1) {
    HttpHeaderOrigin match = createHttpHeaderOrigin();
    match->import("https://developer.mozilla.org:1234");
    if(!match->toString()->equals("https://developer.mozilla.org:1234")){
      printf("---[HttpHeaderOrigin test toString case2] [FAILED]--- \n");
      break;
    }

    break;
  }

  printf("---[HttpHeaderOrigin test toString case100] [OK]--- \n");
}
