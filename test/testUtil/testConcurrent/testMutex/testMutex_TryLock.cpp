#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "Integer.hpp"
#include "AutoLock.hpp"
#include "Mutex.hpp"
#include "System.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

void testMutex_TryLock() {
    TimeWatcher watch = createTimeWatcher();

    while(1) {
      Mutex t = createMutex();
      Thread th = createThread([&t]{
        t->lock();
        usleep(200*1000);
        t->unlock();
      });
      th->start();
      usleep(100*1000);

      watch->start();
      int result = t->tryLock();
      long interval = watch->stop();
      if(result != -LockBusy) {
        printf("---[TestMutex tryLock case1] [FAILED]--- \n");
        break;
      }

      if(interval > 5 || interval < 0) {
        printf("---[TestMutex tryLock case2] [FAILED]--- \n");
        break;
      }

      th->join();
      break;
    }

    while(1) {
      Mutex t = createMutex();
      Thread th = createThread([&t]{
        t->tryLock();
        usleep(200*1000);
        t->unlock();
      });
      th->start();
      usleep(100*1000);

      watch->start();
      t->lock();
      long v = watch->stop();
      if(v < 100 || v > 105) {
        printf("---[TestMutex tryLock case3] [FAILED]--- v is %ld \n",v);
        break;
      }
      break;
    }

    printf("---[TestMutex tryLock case100] [OK]--- \n");
}
