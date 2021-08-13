#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "AutoLock.hpp"
#include "Integer.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

void testConditionNotify() {
    TimeWatcher watch = createTimeWatcher();
    while(1) {
      AtomicInteger v = createAtomicInteger(0);
      Mutex mMutex = createMutex();
      Condition c = createCondition();
      Thread t1 = createThread([&mMutex,&c,&v]{
        AutoLock l(mMutex);
        int ret = c->wait(mMutex);
        if(ret != 0) {
          printf("Condition Notify Case1 test1-------[FAILED],ret is %d \n",ret);
          return;
        }

        v->incrementAndGet();
      });
      t1->start();

      Thread t2 = createThread([&mMutex,&c,&v]{
        AutoLock l(mMutex);
        int ret = c->wait(mMutex);
        if(ret != 0) {
          printf("Condition Notify Case1 test2-------[FAILED] \n");
          return;
        }

        v->incrementAndGet();
      });
      t2->start();

      c->notify();
      usleep(100*1000);
      if(v->get() != 1) {
        printf("Condition Notify Case1 test3-------[FAILED] \n");
      }
      c->notify();

      usleep(100*1000);
      if(v->get() != 2) {
        printf("Condition Notify Case1 test4-------[FAILED] \n");
      }

      printf("Condition Notify Case1 test5-------[OK] \n");
      break;
    }

}
