#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <iostream>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "Condition.hpp"

using namespace obotcha;

std::atomic<int> count(0);

DECLARE_SIMPLE_CLASS(WaitConditionRun) IMPLEMENTS(Runnable) {
public:
  _WaitConditionRun() {
    m = createMutex();
    w = createCondition();
  }

  void run() {
    AutoLock l(m);
    try {
      w->wait(m);
    } catch(InterruptedException &e){
    }
    count++; 
  }

private:
  Mutex m;
  Condition w;
};

//remove condition interrupt because this unit test
int testThreadWaitCondition() {
  printf("---[Thread Test {testThreadWaitCondition()} start]\n");
  for(int i = 0;i<1024*32;i++) {
    Thread t = createThread(createWaitConditionRun());
    //printf("thread trace1 \n");
    t->start();
    //printf("thread trace2 \n");
    t->interrupt();
    //printf("thread trace3 \n");
    t->join();
    //printf("thread trace4 \n");
  }
  printf("---[Thread Test {testThreadWaitCondition()} count is case1] [OK] \n");
  std::cout<<"count is "<<count<<std::endl;
  return 0;
}
