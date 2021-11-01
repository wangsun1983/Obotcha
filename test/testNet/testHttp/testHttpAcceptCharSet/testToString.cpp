#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAcceptCharSet.hpp"

using namespace obotcha;

void testCharSetToString() {
  while(1) {
    HttpAcceptCharSet charset = createHttpAcceptCharSet();
    charset->import("iso-8859-1");
    if(!charset->toString()->equals("iso-8859-1")) {
      printf("---[HttpAcceptCharSet test toString case1] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    HttpAcceptCharSet charset = createHttpAcceptCharSet();
    charset->import("utf-8, iso-8859-1;q=0.5");
    if(!charset->toString()->equals("utf-8, iso-8859-1;q=0.5")) {
      printf("---[HttpAcceptCharSet test toString case2] [FAILED]---,str is %s \n",charset->toString()->toChars());
      break;
    }
    break;
  }

  while(1) {
    HttpAcceptCharSet charset = createHttpAcceptCharSet();
    charset->import("utf-8, iso-8859-1;q=0.5, *;q=0.1");
    if(!charset->toString()->equals("utf-8, iso-8859-1;q=0.5, *;q=0.1")) {
      printf("---[HttpAcceptCharSet test toString case3] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpAcceptCharSet test toString case100] [OK]--- \n");

}
