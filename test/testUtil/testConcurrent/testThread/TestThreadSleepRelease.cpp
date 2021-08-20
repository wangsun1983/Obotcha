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

int myLongSleepExceptionTest1 = 0;
int myLongSleepReleaseTest1 = 0;

DECLARE_CLASS(MyLongSleepTest1Thread) IMPLEMENTS(Thread) {
public:

  void run() {
      try {
        interruptableSleep(50*1000);
      } catch(InterruptedException &e) {
          myLongSleepExceptionTest1 = 1;
      }
  }

  ~_MyLongSleepTest1Thread() {
      myLongSleepReleaseTest1 = 1;
  }
};


int testThreadSleepRelease() {
  printf("---[TestThread Sleep Release Start]--- \n");

  while(1) {
    {
      MyLongSleepTest1Thread t = createMyLongSleepTest1Thread();
      t->start();
      sleep(1);
      printf("t count is %d \n",t->getStrongCount());
      t->interrupt();
    }
    sleep(1);

    if(myLongSleepExceptionTest1 != 1 || myLongSleepReleaseTest1 != 1) {
      printf("---[Thread Test {sleep release()} case1] [FAIL] \n");
      break;
    }

    printf("---[Thread Test {sleep release()} case2] [OK] \n");
    break;
  }

  return 0;

}
