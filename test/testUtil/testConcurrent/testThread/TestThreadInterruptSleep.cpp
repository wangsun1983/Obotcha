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
#include "TimeWatcher.hpp"

using namespace obotcha;

void testThreadInterruptSleep() {
  TimeWatcher watcher = createTimeWatcher();

  while(1) {
    bool isInterrupt = false;
    Thread t = createThread([&isInterrupt]{
      try {
        st(Thread)::interruptableSleep(100);
      } catch(...) {
        isInterrupt = true;
      }
    });
    t->start();

    t->interrupt();
    t->join();
    if(!isInterrupt) {
      printf("---[Thread Test {interruptSleep()} case1] [FAILED]--- \n");
    }
    break;
  }

  while(1) {
    Thread t = createThread([]{
      try {
        st(Thread)::interruptableSleep(100);
      } catch(...) {
      }
    });
    t->start();
    watcher->start();
    t->join();
    long result = watcher->stop();

    if(result < 100 || result > 105) {
      printf("---[Thread Test {interruptSleep()} case2] [FAILED]--- \n");
    }
    break;
  }

  printf("---[Thread Test {interruptSleep()} case100] [OK]--- \n");


}
