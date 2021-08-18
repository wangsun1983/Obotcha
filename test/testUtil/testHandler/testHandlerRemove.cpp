#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"

using namespace obotcha;

DECLARE_CLASS(MyTestHandler2) EXTENDS(Handler) {
public:
  _MyTestHandler2() {
  }

  void handleMessage(Message msg) {
      //printf("msg arg1 is %d \n",msg->arg1);
      count++;
  }

  int count;
};


int testHandlerRemove() {
  //case 1
  while(1) {
    MyTestHandler2 handler = createMyTestHandler2();
    handler->sendEmptyMessageDelayed(1,1000*2);
    handler->sendEmptyMessageDelayed(1,1000*2);
    handler->sendEmptyMessageDelayed(1,1000*2);

    handler->removeMessages(1);
    if(handler->size() != 0) {
      printf("handler size is %d \n",handler->size());
      printf("---[Handler Test {Handler Remove} case1] [FAIL]--- \n");
    }

    printf("---[Handler Test {Handler Remove} case2] [OK]--- \n");
    break;
  }

  //case 2
  while(1) {
    MyTestHandler2 handler = createMyTestHandler2();
    handler->sendEmptyMessageDelayed(1,1000*2);
    handler->sendEmptyMessageDelayed(2,1000*2);
    handler->sendEmptyMessageDelayed(3,1000*2);

    handler->removeMessages(1);
    if(handler->size() != 2) {
      printf("handler size is %d \n",handler->size());
      printf("---[Handler Test {Handler Remove} case3] [FAIL]--- \n");
    }

    printf("---[Handler Test {Handler Remove} case4] [OK]--- \n");
    break;
  }

  printf("---[Handler Test {Handler Remove} case5] [OK]--- \n");
  return 0;
}
