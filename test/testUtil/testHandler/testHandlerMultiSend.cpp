#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyMultiHandler1) EXTENDS(Handler) {
public:
  _MyMultiHandler1() {
  }

  void handleMessage(Message msg) {
      //printf("msg arg1 is %d \n",msg->arg1);
      count++;
  }

  int count;
};

MyMultiHandler1 mulitHandler = createMyMultiHandler1();

DECLARE_SIMPLE_CLASS(SendThread) EXTENDS(Thread) {
public:
  void run() {
    for(int index = 0;index<1024*5;index++) {
      Message msg = createMessage(1);
      msg->arg1 = index;
      mulitHandler->sendMessage(msg);
    }
  }
};

int testHandlerMultiSend() {
  //case 1
  while(1) {
    SendThread t1 = createSendThread();
    SendThread t2 = createSendThread();
    SendThread t3 = createSendThread();
    SendThread t4 = createSendThread();
    SendThread t5 = createSendThread();
    t1->start();
    t2->start();
    t3->start();
    t4->start();
    t5->start();

    t1->join();
    t2->join();
    t3->join();
    t4->join();
    t5->join();
    sleep(10);
    if(mulitHandler->count != 1024*5*5) {
      printf("mulitHandler->count is %d \n",mulitHandler->count);
      printf("---[Handler Test {MultiSend} case1] [FAIL]--- \n");
      return 0;
    }

    printf("---[Handler Test {MultiSend} case2] [OK]--- \n");
    break;
  }

  printf("---[Handler Test {MultiSend} case3] [OK]--- \n");
  return 0;
}
