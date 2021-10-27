#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAcceptPatch.hpp"

using namespace obotcha;

void testPatchToString() {
  while(1) {
    HttpAcceptPatch encoding1 = createHttpAcceptPatch();
    encoding1->import("application/example,text/example");
    if(!encoding1->toString()->equals("application/example,text/example")) {
      printf("---[HttpAcceptPatch test Parse case1] [FAILED]--- \n");
    }
    break;
  }

  while(1) {
    HttpAcceptPatch encoding1 = createHttpAcceptPatch();
    encoding1->import("text/example;charset=utf-8");
    if(!encoding1->toString()->equals("text/example;charset=utf-8")) {
      printf("---[HttpAcceptPatch test Parse case2] [FAILED]--- \n");
    }

    break;
  }

  while(1) {
    HttpAcceptPatch encoding1 = createHttpAcceptPatch();
    encoding1->import("application/merge-patch+json");
    if(!encoding1->toString()->equals("application/merge-patch+json")) {
      printf("---[HttpAcceptPatch test Parse case3] [FAILED]--- \n");
    }
    break;
  }

  printf("---[HttpAcceptPatch test toString case100] [OK]--- \n");

}
