#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpForwarded.hpp"

using namespace obotcha;

void testForwardedToString() {
  while(1) {
    HttpForwarded encoding1 = createHttpForwarded();
    encoding1->import("For=\"[2001:db8:cafe::17]:4711\"");
    if(!encoding1->toString()->equalsIgnoreCase("For=\"[2001:db8:cafe::17]:4711\"")) {
      printf("---[HttpForwarded test toString case1] [FAILED]---,forwarded is %s \n",encoding1->toString()->toChars());
      break;
    }
    break;
  }

  while(1) {
    HttpForwarded encoding1 = createHttpForwarded();
    encoding1->import("for=\"_mdn\"");
    if(!encoding1->toString()->equalsIgnoreCase("for=\"_mdn\"")) {
      printf("---[HttpForwarded test toString case2] [FAILED]--- forwarded is %s\n",encoding1->toString()->toChars());
      break;
    }
    break;
  }

  while(1) {
    HttpForwarded encoding1 = createHttpForwarded();
    encoding1->import("for=192.0.2.60; proto=http; by=203.0.113.43");
    if(encoding1->toString()->equalsIgnoreCase("for=192.0.2.60; proto=http; by=203.0.113.43")) {
      printf("---[HttpForwarded test toString case3] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpForwarded test toString case100] [OK]--- \n");

}
