#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "HttpContentLanguage.hpp"
#include "HttpProtocol.hpp"
using namespace obotcha;

void testToString() {
  while(1) {
    HttpContentLanguage c = createHttpContentLanguage();
    c->import("de-DE, en-CA");
    if(c->toString()->equals("de-DE, en-CA ")) {
      printf("---[HttpContentLanguage test toString case1] [FAILED]--- \n");
    }
    break;
  }

  printf("---[HttpContentLanguage test toString case100] [OK]--- \n");

}
