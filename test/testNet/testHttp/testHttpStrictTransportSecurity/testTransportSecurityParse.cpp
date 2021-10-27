#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpStrictTransportSecurity.hpp"
#include "Math.hpp"

using namespace obotcha;

void testTransportSecurityParse() {
  while(1) {
    HttpStrictTransportSecurity security = createHttpStrictTransportSecurity();
    security->import("max-age=31536000; includeSubDomains;preload");
    if(security->maxAge != 31536000) {
      printf("---[HttpStrictTransportSecurity test Parse case1] [FAILED]--- \n");
      break;
    }

    if(!security->includeSubDomains) {
      printf("---[HttpStrictTransportSecurity test Parse case2] [FAILED]--- \n");
      break;
    }

    if(!security->preload) {
      printf("---[HttpStrictTransportSecurity test Parse case3] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    HttpStrictTransportSecurity security = createHttpStrictTransportSecurity();
    security->import("max-age=31536000");
    if(security->maxAge != 31536000) {
      printf("---[HttpStrictTransportSecurity test Parse case1] [FAILED]--- \n");
      break;
    }

    break;
  }
  printf("---[HttpStrictTransportSecurity test Parse case100] [OK]--- \n");

}
