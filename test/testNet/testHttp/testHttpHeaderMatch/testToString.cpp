#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderMatch.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpHeaderMatch match = createHttpHeaderMatch();
    match->import("\"bfc13a64729c4290ef5b2c2730249c88ca92d82d\"");
    if(!match->toString()->equals("\"bfc13a64729c4290ef5b2c2730249c88ca92d82d\"")) {
      printf("---[HttpHeaderMatch test toString case1] [FAILED]---,s is %s \n",match->toString()->toChars());
    }
    break;
  }

  while(1) {
    HttpHeaderMatch match = createHttpHeaderMatch();
    match->import("W/\"67ab43\", \"54ed21\", \"7892dd\"");
    if(!match->toString()->equals("W/\"67ab43\", \"54ed21\", \"7892dd\"")) {
      printf("---[HttpHeaderMatch test toString case2] [FAILED]--- \n");
    }
    break;
  }

  while(1) {
    HttpHeaderMatch match = createHttpHeaderMatch();
    match->import("*");
    if(!match->toString()->equals("*")) {
      printf("---[HttpHeaderMatch test toString case3] [FAILED]---,match is %s \n",match->toString()->toChars());
    }

    break;
  }

  printf("---[HttpHeaderMatch test toString case100] [OK]--- \n");
}
