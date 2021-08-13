#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "CountDownLatch.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

void testCountDownLatch_MultiThread() {
    TimeWatcher watch = createTimeWatcher();
    while(1) {
      CountDownLatch l = createCountDownLatch(16);
      for(int i = 0;i<16;i++) {
        Thread t = createThread([&l]{
          l->countDown();
        });
        t->start();
      }

      usleep(100*1000);

      if(l->await() != -AlreadyDestroy) {
        printf("---[TestCountDownLatch MultiThread case1] [FAILED]--- \n");
        break;
      }
      break;
    }

    while(1) {
      CountDownLatch l = createCountDownLatch(16);
      AtomicInteger finishCount = createAtomicInteger(0);
      for(int i = 0;i<15;i++) {
        Thread t = createThread([&l,&finishCount]{
          l->countDown();
          l->await();
          finishCount->incrementAndGet();
        });
        t->start();
      }

      if(finishCount->get() != 0) {
        printf("---[TestCountDownLatch MultiThread case2] [FAILED]--- \n");
        break;
      }

      l->countDown();
      usleep(100*1000);
      if(finishCount->get() != 15) {
        printf("---[TestCountDownLatch MultiThread case3] [FAILED]---,value is %d \n",finishCount->get());
        break;
      }
      break;
    }

    printf("---[TestCountDownLatch MultiThread case100] [OK]--- \n");
}
