#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoMutex.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "AtomicInteger.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(LoopThreadJoinRun1) IMPLEMENTS(Runnable) {
public:

  void run() {
      //value->incrementAndGet();
      //printf("sleep1 start\n");
      sleep(5);
      //printf("sleep2 start\n");
  }
};

DECLARE_SIMPLE_CLASS(LoopThreadJoinRun2) IMPLEMENTS(Runnable) {
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
  ArrayList<Thread> list = createArrayList<Thread>();

  for(int i = 0;i<1024*32;i++) {
      //printf("create1 i is %d \n",i);
      Thread t = createThread(createLoopThreadJoinRun1());
      int ret = t->start();
      list->add(t);
  }

  for(int i = 0;i<1024*32;i++) {
      //printf("join1 i is %d \n",i);
      list->get(i)->join();
  }

  list->clear();

  //test2
  ArrayList<Thread> list2 = createArrayList<Thread>();

  for(int i = 0;i<1024*8;i++) {
      //printf("create1 i is %d \n",i);
      Thread t = createThread(createLoopThreadJoinRun2());
      int ret = t->start();
      list2->add(t);
  }

  for(int i = 0;i<1024*8;i++) {
      list2->get(i)->join(10);
  }

  for(int i = 0;i<1024*8;i++) {
      //printf("join1 i is %d \n",i);
      if(list2->get(i)->getStatus() != st(Thread)::Running) {
        printf("---[Thread Test {Loop join()} special case1,is is %d,status is %d \n] [Fail]--- \n",i,list->get(i)->getStatus());
        break;
      }
  }
  for(int i = 0;i<1024*8;i++) {
      //printf("join1 i is %d \n",i);
      list2->get(i)->quit();
  }

  list2->clear();

  printf("---[Thread Test {Loop join()} special case2] [Success]--- \n");

}
