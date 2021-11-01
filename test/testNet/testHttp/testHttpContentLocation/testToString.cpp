#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpContentLocation.hpp"

using namespace obotcha;

void testToString() {
  while(1) {
    HttpContentLocation location = createHttpContentLocation();
    location->import("/index.html");
    if(!location->toString()->equals("/index.html")) {
      printf("---[HttpContentLocation test toString case1] [FAILED]--- ,str is %s\n",location->toString()->toChars());
      break;
    }
    break;
  }

  printf("---[HttpContentLocation test toString case100] [OK]--- \n");

}
