#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAcceptEncoding.hpp"

using namespace obotcha;

void testEncodingToString() {
  while(1) {
    HttpAcceptEncoding encoding1 = createHttpAcceptEncoding();
    encoding1->import("gzip,compress,br");
    if(!encoding1->toString()->equals("gzip,compress,br")) {
      printf("---[HttpAcceptEncoding test toString case1] [FAILED]--- encoding is %s\n",encoding1->toString()->toChars());
    }
    break;
  }

  while(1) {
    HttpAcceptEncoding encoding1 = createHttpAcceptEncoding();
    encoding1->import("deflate,gzip;q=1,*;q=0.5");
    if(!encoding1->toString()->equals("deflate,gzip;q=1,*;q=0.5")) {
      printf("---[HttpAcceptEncoding test toString case2] [FAILED]--- encoding is %s\n",encoding1->toString()->toChars());
    }
    break;
  }

  printf("---[HttpAcceptEncoding test toString case100] [OK]--- \n");

}
