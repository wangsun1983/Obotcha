#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpProxyAuthenticate.hpp"

using namespace obotcha;

void testProxyAuthenticateToString() {
  while(1) {
    HttpProxyAuthenticate proxyAuth = createHttpProxyAuthenticate();
    proxyAuth->import("Basic");

    if(!proxyAuth->toString()->equals("Basic")) {
        printf("---[HttpProxyAuthenticate test toString case1] [FAILED]--- \n");
        break;
    }
    break;
  }

  while(1) {
    HttpProxyAuthenticate proxyAuth = createHttpProxyAuthenticate();
    proxyAuth->import("Basic realm=\"Access to the internal site\"");

    if(!proxyAuth->toString()->equals("Basic realm=\"Access to the internal site\"")) {
        printf("---[HttpProxyAuthenticate test toString case2] [FAILED]--- auth is %s\n",proxyAuth->toString()->toChars());
        break;
    }

    break;
  }

  printf("---[HttpProxyAuthenticate test toString case100] [OK]--- \n");

}
