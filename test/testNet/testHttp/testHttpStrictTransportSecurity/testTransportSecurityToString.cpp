#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpStrictTransportSecurity.hpp"

using namespace obotcha;

void testTransportSecurityToString() {
  while(1) {
    HttpStrictTransportSecurity security = createHttpStrictTransportSecurity();
    security->import("max-age=31536000;preload,includeSubDomains");
    if(!security->toString()->equals("max-age=31536000;preload;includeSubDomains")) {
      printf("---[HttpStrictTransportSecurity test toString case1] [FAILED]---,security is %s \n",security->toString()->toChars());
      break;
    }
    break;
  }

  while(1) {
    HttpStrictTransportSecurity security = createHttpStrictTransportSecurity();
    security->import("max-age=31536000");
    if(!security->toString()->equals("max-age=31536000")) {
      printf("---[HttpStrictTransportSecurity test toString case2] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpStrictTransportSecurity test toString case100] [OK]--- \n");
}
