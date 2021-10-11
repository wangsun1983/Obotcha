#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpProxyAuthorization.hpp"

using namespace obotcha;

void testProxyAUthorizationToString() {
  while(1) {
    HttpProxyAuthorization proxy = createHttpProxyAuthorization();
    proxy->import("Basic YWxhZGRpbjpvcGVuc2VzYW1l");
    if(!proxy->toString()->equals("Basic YWxhZGRpbjpvcGVuc2VzYW1l")) {
      printf("---[HttpProxyAuthorization test toString case10] [OK]--- \n");
    }
    break;
  }

  printf("---[HttpProxyAuthorization test toString case100] [OK]--- \n");
}
