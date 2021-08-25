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

void testConditionDoubleLock() {
    TimeWatcher watch = createTimeWatcher();
    while(1) {
      Mutex mMutex = createMutex();

      Condition c0 = createCondition();
      Condition c1 = createCondition();
      Condition c2 = createCondition();

      Thread t0 = createThread([&mMutex,&c0]{
        usleep(10*1000);
        printf("thread0 start wait \n");
        AutoLock l(mMutex);
        c0->wait(mMutex);
        printf("thread0 finish wait \n");
      });
      t0->start();

      Thread t1 = createThread([&mMutex,&c1]{
        usleep(10*1000);
        printf("thread1 start wait \n");
        AutoLock l(mMutex);
        c1->wait(mMutex);
        printf("thread1 finish wait \n");
      });
      t1->start();

      Thread t2 = createThread([&mMutex,&c2,&c1,&c0]{
        AutoLock l(mMutex);
        printf("thread2 start wait \n");
        c2->wait(mMutex,100);
        printf("thread2 finish wait \n");
        c1->notify();
        c0->notify();
      });
      t2->start();

      t0->join();
      t1->join();
      t2->join();
      printf("Condition Wait Case1 test2-------[OK] \n");
      break;
    }

}
