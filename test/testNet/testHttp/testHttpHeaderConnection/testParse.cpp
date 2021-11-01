#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderConnection.hpp"
#include "Math.hpp"

using namespace obotcha;

void testConnectionParse() {
  while(1) {
    HttpHeaderConnection connection = createHttpHeaderConnection();
    connection->import(" keep-alive");
    if(!connection->get()->equals("keep-alive")) {
      printf("---[HttpHeaderConnection test Parse case1] [FAILED]--- \n");
    }
    break;
  }

  while(1) {
    HttpHeaderConnection connection = createHttpHeaderConnection();
    connection->import("close");
    if(!connection->get()->equals("close")) {
      printf("---[HttpHeaderConnection test Parse case2] [FAILED]--- \n");
    }
    break;
  }


  printf("---[HttpHeaderConnection test Parse case100] [OK]--- \n");

}
