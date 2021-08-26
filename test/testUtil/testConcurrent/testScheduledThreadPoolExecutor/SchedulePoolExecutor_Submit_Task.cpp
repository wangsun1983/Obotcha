#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ThreadScheduledPoolExecutor.hpp"
#include "Integer.hpp"
#include "ExecutorBuilder.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "ThreadScheduledPoolExecutor.hpp"
#include "Long.hpp"
#include "TimeWatcher.hpp"
#include "CountDownLatch.hpp"

using namespace obotcha;

void testSubmitTask() {
  TimeWatcher watch = createTimeWatcher();

  while(1) {
    Mutex taskMutex = createMutex();
    Condition condition = createCondition();

    auto pool = createExecutorBuilder()
              ->setQueueSize(1)
              ->setMaxThreadNum(3)
              ->newScheduledThreadPool();
    auto f1 = pool->submit(100,[&taskMutex,&condition]{
      AutoLock l(taskMutex);
      condition->notify();
    });

    watch->start();
    AutoLock l(taskMutex);
    condition->wait(taskMutex);
    long result = watch->stop();

    if(result < 100 || result > 105) {
      printf("---[ScheduledThreadPoolExecutor SubmitTask case1] [FAILED]--- \n");
      break;
    }
    pool->shutdown();
    pool->awaitTermination();
    break;
  }

  while(1) {
    CountDownLatch latch = createCountDownLatch(32);
    auto pool = createExecutorBuilder()
              ->setQueueSize(64)
              ->setMaxThreadNum(3)
              ->newScheduledThreadPool();
    for(int i = 0;i<32;i++) {
      auto f1 = pool->submit(100,[&latch]{
        latch->countDown();
      });
    }

    watch->start();
    latch->await(300);
    long result = watch->stop();
    if(result < 100 || result > 105) {
      printf("---[ScheduledThreadPoolExecutor SubmitTask case2] [FAILED]--- \n");
      break;
    }
    pool->shutdown();
    pool->awaitTermination();
    break;
  }

  while(1) {
    CountDownLatch latch = createCountDownLatch(256);
    auto pool = createExecutorBuilder()
              ->setQueueSize(1024)
              ->setMaxThreadNum(16)
              ->newScheduledThreadPool();
    for(int i = 0;i<256;i++) {
      auto f1 = pool->submit(100,[&latch]{
        latch->countDown();
      });
    }

    watch->start();
    latch->await(300);
    long result = watch->stop();
    if(result < 100 || result > 105 ) {
      printf("---[ScheduledThreadPoolExecutor SubmitTask case3] [FAILED]--- \n");
      break;
    }
    pool->shutdown();
    pool->awaitTermination();
    break;
  }

  while(1) {
    CountDownLatch latch = createCountDownLatch(32);
    auto pool = createExecutorBuilder()
              ->setQueueSize(1024)
              ->setMaxThreadNum(16)
              ->newScheduledThreadPool();
    for(int i = 0;i<31;i++) {
      auto f1 = pool->submit(100,[&latch]{
        latch->countDown();
      });
    }

    watch->start();
    latch->await(300);
    long result = watch->stop();
    if(result < 300 || result > 305) {
      printf("---[ScheduledThreadPoolExecutor SubmitTask case4] [FAILED]--- \n");
      break;
    }
    pool->shutdown();
    pool->awaitTermination();
    break;
  }
  printf("---[ScheduledThreadPoolExecutor SubmitTask case100] [OK]--- \n");
}
