#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderDigest.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpHeaderDigest digest = createHttpHeaderDigest();
    digest->import(" sha-256=X48E9qOokqqrvdts8nOJRJN3OWDUoyWxBf7kbu9DBPE=");
    if(!digest->toString()->equals("sha-256=X48E9qOokqqrvdts8nOJRJN3OWDUoyWxBf7kbu9DBPE=")) {
      printf("---[testHttpHeaderDigest test toString case1] [FAILED]--- \n");
    }

    break;
  }

  while(1) {
    HttpHeaderDigest digest = createHttpHeaderDigest();
    digest->import(" sha-256=X48E9qOokqqrvdts8nOJRJN3OWDUoyWxBf7kbu9DBPE=,unixsum=30637");
    if(!digest->toString()->equals("sha-256=X48E9qOokqqrvdts8nOJRJN3OWDUoyWxBf7kbu9DBPE=,unixsum=30637")) {
      printf("---[testHttpHeaderDigest test toString case2] [FAILED]--- \n");
    }
    break;
  }

  printf("---[testHttpHeaderDigest test toString case100] [OK]--- \n");
}
