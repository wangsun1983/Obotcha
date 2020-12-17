#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyHandler1) EXTENDS(Handler) {
public:
  _MyHandler1() {

  }

  void handleMessage(Message msg) {

  }

  int count;
  int delayedCount;
};

int testHandlerSize() {
  //case 1
  while(1) {
    MyHandler1 handler1 = createMyHandler1();
    handler1->sendEmptyMessageDelayed(1,1000*10);
    handler1->sendEmptyMessageDelayed(2,1000*10);
    handler1->sendEmptyMessageDelayed(3,1000*10);
    handler1->sendEmptyMessageDelayed(4,1000*10);

    if(handler1->size() != 4) {
      printf("---[Handler Test {Normal size()} case1] [FAILED]--- \n");
      return 0;
    }

    printf("---[Handler Test {Normal size()} case2] [OK]--- \n");
    break;
  }

  //case 2
  while(1) {
    MyHandler1 handler1 = createMyHandler1();
    handler1->sendEmptyMessage(1);
    handler1->sendEmptyMessageDelayed(2,1000*10);
    handler1->sendEmptyMessageDelayed(3,1000*10);
    handler1->sendEmptyMessageDelayed(4,1000*10);
    usleep(100);
    if(handler1->size() != 3) {
      printf("---[Handler Test {Normal size()} case3] [FAILED]--- \n");
      return 0;
    }

    printf("---[Handler Test {Normal size()} case4] [OK]--- \n");
    break;
  }

  //case 3
  while(1) {
    MyHandler1 handler1 = createMyHandler1();
    handler1->sendEmptyMessage(1);
    handler1->sendEmptyMessage(2);
    handler1->sendEmptyMessage(3);
    usleep(100*5);
    if(handler1->size() != 0) {
      printf("---[Handler Test {Normal size()} case5] [FAILED]--- \n");
      return 0;
    }

    printf("---[Handler Test {Normal size()} case6] [OK]--- \n");
    break;
  }

  printf("---[Handler Test {Normal size()} case7] [OK]--- \n");
  return 0;
}
