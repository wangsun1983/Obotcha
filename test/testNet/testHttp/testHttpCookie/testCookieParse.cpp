#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpCookieParser.hpp"

using namespace obotcha;

void testCookieParse() {
  while(1) {
    String cookie = "yummy_cookie=choco; tasty_cookie=strawberry";
    ArrayList<HttpCookie> cookies = st(HttpCookieParser)::parse(cookie);
    if(cookies == nullptr || cookies->size() != 2) {
      printf("---[HttpCookie test Parse case1] [FAILED]--- \n");
      break;
    }

    auto cookie1 = cookies->get(0);
    if(!cookie1->getName()->equals("yummy_cookie") || !cookie1->getValue()->equals("choco")) {
      printf("---[HttpCookie test Parse case2] [FAILED]--- \n");
      break;
    }

    auto cookie2 = cookies->get(1);
    if(!cookie2->getName()->equals("tasty_cookie") || !cookie2->getValue()->equals("strawberry")) {
      printf("---[HttpCookie test Parse case3] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpCookie test Parse case100] [OK]--- \n");

}
