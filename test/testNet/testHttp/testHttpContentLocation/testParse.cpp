#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpContentLocation.hpp"
#include "Math.hpp"

using namespace obotcha;

void testParse() {
  while(1) {
    HttpContentLocation location = createHttpContentLocation();
    location->import("/index.html");
    if(location->get() == nullptr || !location->get()->equals("/index.html")) {
      printf("---[HttpContentLocation test Parse case1] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[HttpContentLocation test Parse case100] [OK]--- \n");

}
