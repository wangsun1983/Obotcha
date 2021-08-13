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

int testMutex_UnLock() {
    TimeWatcher watch = createTimeWatcher();

    while(1) {
      Mutex t = createMutex();
      t->unlock();
      Thread th = createThread([&t]{
        t->lock();
        usleep(300*1000);
        t->unlock();
      });
      th->start();
      usleep(100*1000);

      watch->start();
      t->unlock();
      int v = t->lock(100);
      long result = watch->stop();
      if(v != -WaitTimeout) {
        printf("---[TestMutex UnLock case1] [FAIL]--- ,v is %d\n",v);
        break;
      }

      if(result < 100 || result > 105) {
        printf("---[TestMutex UnLock case2] [FAIL]--- \n");
        break;
      }
      break;
    }

    printf("---[TestMutex UnLock case100] [OK]--- \n");
}
