#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"

using namespace obotcha;


void testHandlerLambda() {
  printf("---[HandlerLambda Test Start]--- \n");
  Handler h = createHandler();
  while(1) {
    int value = 100;
    h->post([&value]() {
      if(value == 100) {
        value = 123;
      }
    });
    sleep(1);

    if(value != 123) {
      printf("---[HandlerLambda Test Start case1] [FAILED]--- \n");
      break;
    }

    printf("---[HandlerLambda Test Start case2] [OK]--- \n");
    break;
  }

  while(1) {
    int value = 100;
    long current = st(System)::currentTimeMillis();
    long next = 0;
    h->postDelayed(3000,[&next]() {
      next = st(System)::currentTimeMillis();
    });
    sleep(4);
    printf("next is %ld,current is %ld \n",next,current);

    if(next - current > 3005 || current - next > 3005) {
      printf("---[HandlerLambda Test case3] [FAILED]--- \n");
      break;
    }

    printf("---[HandlerLambda Test case4] [OK]--- \n");
    break;
  }
}
