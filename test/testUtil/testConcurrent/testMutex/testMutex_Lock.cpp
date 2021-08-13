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

int testMutex_Lock() {
    TimeWatcher watch = createTimeWatcher();

    while(1) {
      Mutex t = createMutex();
      watch->start();
      t->lock(100);
      t->lock(100);
      long result = watch->stop();
      if(result < 0 || result > 5) {
        printf("---[TestMutex Lock case1] [FAIL]--- \n");
        break;
      }
      break;
    }

    while(1) {
      Mutex t = createMutex(st(Mutex)::Normal);
      watch->start();
      t->lock(100);
      t->lock(100);
      long result = watch->stop();
      if(result < 100 || result > 105) {
        printf("---[TestMutex Lock case2] [FAIL]--- \n");
        break;
      }
      break;
    }

    while(1) {
      Mutex t = createMutex();
      Thread t1 = createThread([&t]{
        t->lock(300);
      });
      t1->start();
      usleep(100*1000);
      watch->start();
      long ret = t->lock(100);
      long result = watch->stop();
      if(ret != -WaitTimeout) {
        printf("---[TestMutex Lock case3_1] [FAIL]---,ret is %d \n",ret);
        break;
      }

      if(result < 100 || result > 105) {
        printf("---[TestMutex Lock case3] [FAIL]---,result is %d \n",result);
        break;
      }
      break;
    }

    while(1) {
      Mutex t = createMutex();
      AtomicInteger count = createAtomicInteger(0);
      t->lock();

      Thread t1 = createThread([&t,&count]{
        t->lock();
        count->incrementAndGet();
      });
      t1->start();

      usleep(100*1000);
      if(count->get() != 0) {
        printf("---[TestMutex Lock case4] [FAIL]--- \n");
        break;
      }
      t->unlock();
      usleep(10*1000);
      if(count->get() != 1) {
        printf("---[TestMutex Lock case5] [FAIL]--- \n");
        break;
      }
      break;
    }
    printf("---[TestMutex Lock case100] [OK]--- \n");
}
