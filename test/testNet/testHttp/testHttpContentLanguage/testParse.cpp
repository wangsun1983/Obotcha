#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpAccept.hpp"
#include "Math.hpp"
#include "HttpAllow.hpp"
#include "HttpContentLanguage.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpContentLanguage c = createHttpContentLanguage();
    c->import("de-DE, en-CA");
    auto list = c->get();
    if(!list->get(0)->equals("de-DE")) {
      printf("---[HttpContentLanguage test Parse case1] [FAILED]--- \n");
      break;
    }

    if(!list->get(1)->equals("en-CA")) {
      printf("---[HttpContentLanguage test Parse case2] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpContentLanguage test Parse case100] [OK]--- \n");

}
