#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "System.hpp"
#include "Error.hpp"

using namespace obotcha;

DECLARE_CLASS(LoopThreadJoinRun1) IMPLEMENTS(Runnable) {
public:

  void run() {
      //value->incrementAndGet();
      //printf("sleep1 start\n");
      st(Thread)::msleep(5);
      //printf("sleep2 start\n");
  }
};

DECLARE_CLASS(LoopThreadJoinRun2) IMPLEMENTS(Runnable) {
public:

  void run() {
      //value->incrementAndGet();
      //printf("sleep1 start\n");
      sleep(1000);
      //printf("sleep2 start\n");
  }
};

int testThreadLoopJoin() {
  //test1
  printf("trace1 \n");
  ArrayList<Thread> list = createArrayList<Thread>();

  for(int i = 0;i<1024*32;i++) {
      Thread t = createThread(createLoopThreadJoinRun1());
      int ret = t->start();
      list->add(t);
  }
  printf("trace2 \n");
  for(int i = 0;i<1024*32;i++) {
      list->get(i)->join();
  }

  list->clear();
  printf("trace3 \n");
  //test2
  ArrayList<Thread> list2 = createArrayList<Thread>();

  for(int i = 0;i<1024*8;i++) {
      Thread t = createThread(createLoopThreadJoinRun2());
      int ret = t->start();
      list2->add(t);
  }
  printf("trace4 \n");
  for(int i = 0;i<1024*8;i++) {
      list2->get(i)->join(10);
  }
  printf("trace5 \n");
  for(int i = 0;i<1024*8;i++) {
      if(list2->get(i)->getStatus() != st(Thread)::Running) {
        printf("---[Thread Test {Loop join()} special case1,is is %d,status is %d \n] [Fail]--- \n",i,list->get(i)->getStatus());
        break;
      }
  }
  printf("trace6 \n");
  //for(int i = 0;i<1024*8;i++) {
  //    list2->get(i)->quit();
  //}
  printf("trace7 \n");
  list2->clear();

  printf("---[Thread Test {Loop join()} special case2] [Success]--- \n");

}
