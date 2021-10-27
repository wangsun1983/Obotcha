#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpProxyAuthenticate.hpp"
#include "Math.hpp"

using namespace obotcha;

void testProxyAuthenticateParse() {
  while(1) {
    HttpProxyAuthenticate proxyAuth = createHttpProxyAuthenticate();
    proxyAuth->import("Basic");

    if(!proxyAuth->type->equals("Basic")) {
        printf("---[HttpProxyAuthenticate test Parse case1] [FAILED]--- \n");
        break;
    }
    break;
  }

  while(1) {
    HttpProxyAuthenticate proxyAuth = createHttpProxyAuthenticate();
    proxyAuth->import("Basic realm=\"Access to the internal site\"");

    if(!proxyAuth->type->equals("Basic")) {
        printf("---[HttpProxyAuthenticate test Parse case2] [FAILED]--- \n");
        break;
    }

    if(!proxyAuth->realm->equals("Access to the internal site")) {
        printf("---[HttpProxyAuthenticate test Parse case3] [FAILED]--- \n");
        break;
    }
    break;
  }

  printf("---[HttpProxyAuthenticate test Parse case100] [OK]--- \n");

}
