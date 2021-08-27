#include <stdio.h>
#include <unistd.h>
#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ThreadPriorityPoolExecutor.hpp"
#include "Integer.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "ExecutorBuilder.hpp"
#include "TimeWatcher.hpp"
#include "CountDownLatch.hpp"

using namespace obotcha;

void testSubmitMultiThread() {
  TimeWatcher watch = createTimeWatcher();
  while(1) {
    CountDownLatch latch = createCountDownLatch(32*1024*3);

    auto pool = createExecutorBuilder()
              ->setQueueSize(32)
              ->setThreadNum(4)
              ->newPriorityThreadPool();
    Mutex mutex1 = createMutex();
    int count1 = 0;

    Mutex mutex2 = createMutex();
    int count2 = 0;

    Mutex mutex3 = createMutex();
    int count3 = 0;

    Thread t1 = createThread([&count1,&pool,&latch,&mutex1]{
      for(int i = 0;i<1024*32;i++) {
        pool->submit(st(Executor)::Low,[&count1,&latch,&mutex1]{
          {
            AutoLock l(mutex1);
            count1 = count1 + 1;
          }
          latch->countDown();
        });
      }
    });
    t1->start();

    Thread t2 = createThread([&count2,&pool,&latch,&mutex2]{
      for(int i = 0;i<1024*32;i++) {
        pool->submit(st(Executor)::Medium,[&count2,&latch,&mutex2]{
          {
            AutoLock l(mutex2);
            count2 = count2 + 2;
          }
          latch->countDown();
        });
      }
    });
    t2->start();

    Thread t3 = createThread([&count3,&pool,&latch,&mutex3]{
      for(int i = 0;i<1024*32;i++) {
        pool->submit(st(Executor)::High,[&count3,&latch,&mutex3]{
          {
            AutoLock l(mutex3);
            count3 = count3 + 3;
          }
          latch->countDown();
        });
      }
    });
    t3->start();

    latch->await();
    int sum1 = 0;
    int sum2 = 0;
    int sum3 = 0;

    for(int i = 0;i < 1024*32;i++) {
      sum1 = sum1 + 1;
    }

    for(int i = 0;i < 1024*32;i++) {
      sum2 = sum2 + 2;
    }

    for(int i = 0;i < 1024*32;i++) {
      sum3 = sum3 + 3;
    }

    if(sum1 != count1) {
      printf("---[TestPriorityPoolExecutor MultiThread Test case1] [FAILED]--- sum1 is %d,count1 is %d\n",sum1,count1);
      //break;
    }

    if(sum2 != count2) {
      printf("---[TestPriorityPoolExecutor MultiThread Test case2] [FAILED]--- sum2 is %d,count2 is %d\n",sum2,count2);
      //break;
    }

    if(sum3 != count3) {
      printf("---[TestPriorityPoolExecutor MultiThread Test case3] [FAILED]--- sum3 is %d,count3 is %d\n",sum3,count3);
      //break;
    }

    pool->shutdown();
    pool->awaitTermination();
    break;
  }

  printf("---[TestPriorityPoolExecutor SubmitPriority Test case100] [OK]--- \n");
}
