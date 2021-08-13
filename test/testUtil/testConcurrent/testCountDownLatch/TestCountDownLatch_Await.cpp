#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "CountDownLatch.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

void testCountDownLatch_Await() {
    TimeWatcher watcher = createTimeWatcher();
    while(1) {
      CountDownLatch latch = createCountDownLatch(1);
      Thread t = createThread([&latch]{
        usleep(200*1000);
        latch->countDown();
      });
      t->start();
      watcher->start();
      latch->await(100);
      long result = watcher->stop();
      if(result < 100 || result > 105) {
        printf("---[TestCountDownLatch await case1] [FAILED]---,result is %ld \n",result);
        break;
      }

      t->join();
      watcher->start();
      latch->await(100);
      result = watcher->stop();
      if(result > 5) {
        printf("---[TestCountDownLatch await case2] [FAILED]---,result is %ld \n",result);
        break;
      }
      break;
    }



    printf("---[TestCountDownLatch CountDown case100] [OK]--- \n");
}
