#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderPragma.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpHeaderPragma pragma = createHttpHeaderPragma();
    pragma->import(" no-cache ");
    if(!pragma->toString()->equals("no-cache")){
      printf("---[HttpHeaderPragma test toString case1] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpHeaderPragma test toString case100] [OK]--- \n");
}
