#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "CountDownLatch.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

void testCountDownLatch_CountDown() {
    TimeWatcher watcher = createTimeWatcher();
    while(1) {
      CountDownLatch latch = createCountDownLatch(1);
      Thread t = createThread([&latch]{
        usleep(100*1000);
        latch->countDown();
      });
      t->start();
      watcher->start();
      latch->await();
      long result = watcher->stop();
      if(result < 100 || result > 105) {
        printf("---[TestCountDownLatch CountDown case1] [FAILED]--- \n");
        break;
      }
      break;
    }

    while(1) {
      CountDownLatch latch = createCountDownLatch(2);
      Thread t = createThread([&latch]{
        usleep(100*1000);
        latch->countDown();
      });
      t->start();
      watcher->start();
      latch->await(200);
      long result = watcher->stop();
      if(result < 200 || result > 205) {
        printf("---[TestCountDownLatch CountDown case2] [FAILED]--- \n");
        break;
      }
      break;
    }

    while(1) {
      CountDownLatch latch = createCountDownLatch(2);
      if(latch->countDown() != 0) {
        printf("---[TestCountDownLatch CountDown case3] [FAILED]--- \n");
        break;
      }

      if(latch->countDown() != 0) {
        printf("---[TestCountDownLatch CountDown case4] [FAILED]--- \n");
        break;
      }

      if(latch->countDown() != -AlreadyDestroy) {
        printf("---[TestCountDownLatch CountDown case5] [FAILED]--- \n");
        break;
      }
      break;
    }

    printf("---[TestCountDownLatch CountDown case100] [OK]--- \n");
}
