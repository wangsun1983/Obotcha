#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpProxyAuthorization.hpp"
#include "Math.hpp"

using namespace obotcha;

void testProxyAUthorizationParse() {
  while(1) {
    HttpProxyAuthorization proxy = createHttpProxyAuthorization();
    proxy->import("Basic YWxhZGRpbjpvcGVuc2VzYW1l");
    if(!proxy->type->equals("Basic")) {
      printf("---[HttpProxyAuthorization test Parse case10] [OK]--- \n");
    }

    if(!proxy->credentials->equals("YWxhZGRpbjpvcGVuc2VzYW1l")) {
      printf("---[HttpProxyAuthorization test Parse case10] [OK]--- \n");
    }

    break;
  }

  printf("---[HttpProxyAuthorization test Parse case100] [OK]--- \n");
}
