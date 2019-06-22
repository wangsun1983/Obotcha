#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "CountDownLatch.hpp"
#include "Thread.hpp"
#include "System.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyThread1) IMPLEMENTS(Thread) {
public:
  _MyThread1(CountDownLatch lat) {
    latch = lat;
  }

  void run() {
      st(Thread)::msleep(5000);
      latch->countDown();
  }

private:
  CountDownLatch latch;
};

int main() {
    printf("---[TestScheduledThreadPoolExecutor Test Start]--- \n");

    //await()
    while(1) {
        CountDownLatch latch = createCountDownLatch(2);
        MyThread1 t1 = createMyThread1(latch);
        MyThread1 t2 = createMyThread1(latch);
        t1->start();
        t2->start();
        long time1 = st(System)::currentTimeMillis();
        latch->await();
        long time2 = st(System)::currentTimeMillis();

        if(time2 - time1 >5005) {
            printf("---[TestScheduledThreadPoolExecutor Test {await()} case1] [FAILED]--- \n");
            break;
        }

        printf("---[TestScheduledThreadPoolExecutor Test {await()} case2] [Success]--- \n");
        break;
    }

    //await(long)
    while(1) {
        CountDownLatch latch = createCountDownLatch(2);
        MyThread1 t1 = createMyThread1(latch);
        MyThread1 t2 = createMyThread1(latch);
        t1->start();
        t2->start();
        long time1 = st(System)::currentTimeMillis();
        int waitret = latch->await(2000);
        long time2 = st(System)::currentTimeMillis();

        if(time2 - time1 >2005) {
            printf("---[TestScheduledThreadPoolExecutor Test {await(long)} case1] [FAILED]--- \n");
            break;
        }

        if(waitret != -CountDownLatchWaitTimeout) {
            printf("---[TestScheduledThreadPoolExecutor Test {await(long)} case2] [FAILED]--- \n");
            break;
        }

        printf("---[TestScheduledThreadPoolExecutor Test {await()} case3] [Success]--- \n");
        break;
    }
    
    //countDown
    while(1) {
      CountDownLatch latch = createCountDownLatch(2);
      latch->countDown();
      latch->countDown();
      int ret = latch->countDown();
      if(ret != -CountDownLatchAlreadyZero) {
          printf("---[TestScheduledThreadPoolExecutor Test {countDown()} case1] [FAILED]--- \n");
          break;
      }

      printf("---[TestScheduledThreadPoolExecutor Test {countDown()} case2] [Success]--- \n");
      break;
    }
}
