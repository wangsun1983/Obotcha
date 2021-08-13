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

void testConditionWait() {
    TimeWatcher watch = createTimeWatcher();
    while(1) {
      Mutex mMutex = createMutex();
      Condition c = createCondition();
      long result = 0;
      Thread t = createThread([&mMutex,&c,&result,&watch]{
        watch->start();
        AutoLock l(mMutex);
        int ret = c->wait(mMutex,100);
        result = watch->stop();
      });
      t->start();

      usleep(1000*200);
      if(result < 100 || result > 105) {
        printf("Condition Wait Case1 test1-------[FAILED],result is %ld\n",result);
        break;
      }

      printf("Condition Wait Case1 test2-------[OK] \n");
      break;
    }

    while(1) {
      Mutex mMutex = createMutex();
      Condition c = createCondition();
      AutoLock l(mMutex);
      watch->start();
      int ret = c->wait(mMutex,300);
      if(ret != -WaitTimeout) {
        printf("Condition Wait Case1 test3-------[FAILED] \n");
        break;
      }
      long interval = watch->stop();
      if(interval > 305 || interval < 300) {
        printf("Condition Wait Case1 test4-------[FAILED],interval is %ld \n",interval);
        break;
      }
      printf("Condition Wait Case1 test5-------[OK],interval is %ld \n",interval);
      break;
    }

    while(1) {
      Mutex mMutex = createMutex();
      Condition c = createCondition();
      long result = 0;
      Thread t = createThread([&c]{
        usleep(100*1000);
        c->notify();
      });
      t->start();

      AutoLock l(mMutex);
      watch->start();
      c->wait(mMutex);
      result = watch->stop();
      if(result < 100 || result > 105) {
        printf("Condition Wait Case1 test6-------[FAILED] \n");
        break;
      }

      printf("Condition Wait Case1 test7-------[OK] \n");
      break;
    }
}
