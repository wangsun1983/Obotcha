#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "HttpMime.hpp"
#include "HttpHeaderConnection.hpp"

using namespace obotcha;

void testConnectionToString() {
  while(1) {
    HttpHeaderConnection connection = createHttpHeaderConnection();
    connection->import(" keep-alive");
    if(!connection->toString()->equals("keep-alive")) {
      printf("---[HttpHeaderConnection test toString case1] [FAILED]--- \n");
    }
    break;
  }

  printf("---[HttpForwarded test toString case100] [OK]--- \n");

}
