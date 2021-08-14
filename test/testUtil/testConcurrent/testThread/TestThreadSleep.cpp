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
#include "InterruptedException.hpp"


using namespace obotcha;

int count = 0;

DECLARE_SIMPLE_CLASS(SleepRun1) IMPLEMENTS(Runnable) {
public:

  void run() {
      try {
        st(Thread)::msleep(100000000);
      } catch(InterruptedException e){}
      count++;
  }

};


int testThreadSleep() {
  printf("---[TestThread Sleep Start]--- \n");

  while(1) {
    for(int i = 0;i < 1024*32;i++) {
      Thread t = createThread(createSleepRun1());
      t->start();
      t->interrupt();
      t->join();
    }
    printf("---[Thread Test {sleep()} Interrupt case1] [Success],count is %d--- \n",count);
    break;
  }

  return 0;

}
