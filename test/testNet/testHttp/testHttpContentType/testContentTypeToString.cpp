#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpContentType.hpp"

using namespace obotcha;

void testContentTypeToString() {
  while(1) {
    HttpContentType contentType1 = createHttpContentType();
    contentType1->import("text/html;charset=utf-8");
    if(!contentType1->toString()->equals("text/html;charset=utf-8")) {
      printf("---[HttpContentType test toString case1] [FAILED]---,type is %s \n",contentType1->toString()->toChars());
      return;
    }

    HttpContentType contentType2 = createHttpContentType();
    contentType2->import("multipart/form-data;boundary=something");
    if(!contentType2->toString()->equals("multipart/form-data;boundary=something")) {
      printf("---[HttpContentType test toString case3] [FAILED]---,type is %s \n",contentType1->toString()->toChars());
      return;
    }
    break;
  }
  printf("---[HttpContentType test toString case100] [OK]--- \n");

}
