#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpContentDisposition.hpp"

using namespace obotcha;

void testDispositionToString() {
  while(1) {
    HttpContentDisposition disposition = createHttpContentDisposition();
    disposition->import("attachment");
    if(!disposition->toString()->equals("attachment")) {
        printf("---[HttpContentDisposition test toString case1] [FAILED]---,disposition is %s \n",disposition->toString()->toChars());
        break;
    }
    break;
  }

  while(1) {
    HttpContentDisposition disposition = createHttpContentDisposition();
    disposition->import("attachment; filename=\"filename.jpg\"");
    if(!disposition->toString()->equals("attachment; filename=\"filename.jpg\"")) {
        printf("---[HttpContentDisposition test toString case2] [FAILED]---,disposition is %s \n",disposition->toString()->toChars());
        break;
    }
    break;
  }

  while(1) {
    HttpContentDisposition disposition = createHttpContentDisposition();
    disposition->import("form-data; name=\"fieldName\"; filename=\"filename.jpg\"");
    if(!disposition->toString()->equals("form-data; name=\"fieldName\"; filename=\"filename.jpg\"")) {
        printf("---[HttpContentDisposition test toString case3] [FAILED]--- disposition is %s \n",disposition->toString()->toChars());
        break;
    }
    break;
  }
  printf("---[HttpContentDisposition test toString case100] [OK]--- \n");

}
