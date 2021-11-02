#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderPragma.hpp"
#include "Math.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpHeaderPragma pragma = createHttpHeaderPragma();
    pragma->import(" no-cache ");
    if(!pragma->get()->equals("no-cache")){
      printf("---[HttpHeaderPragma test parse case1] [FAILED]--- \n");
      break;
    }
    break;
  }
  
  printf("---[HttpHeaderPragma test Parse case100] [OK]--- \n");
}
