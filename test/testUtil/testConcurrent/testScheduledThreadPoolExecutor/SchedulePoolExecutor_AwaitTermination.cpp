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

void testAwaitTermination() {
  TimeWatcher watch = createTimeWatcher();

  while(1) {
    auto pool = createExecutorBuilder()
              ->setQueueSize(1)
              ->setMaxThreadNum(3)
              ->newScheduledThreadPool();
    pool->submit(100,[]{

    });

    pool->shutdown();
    watch->start();
    pool->awaitTermination();
    long result = watch->stop();
    if(result < 0 || result > 5) {
      printf("---[ScheduledThreadPoolExecutor awaitTermination case1] [FAILED]--- \n");
    }
    break;
  }

  while(1) {
    auto pool = createExecutorBuilder()
              ->setQueueSize(1)
              ->setMaxThreadNum(3)
              ->newScheduledThreadPool();
    pool->submit(0,[]{
      usleep(200*1000);
    });
    usleep(100*1000);
    pool->shutdown();
    watch->start();
    pool->awaitTermination();
    long result = watch->stop();
    if(result < 100 || result > 205) {
      printf("---[ScheduledThreadPoolExecutor awaitTermination case2] [FAILED]--- ,result is %ld\n",result);
    }
    break;
  }

  while(1) {
    auto pool = createExecutorBuilder()
              ->setQueueSize(1)
              ->setMaxThreadNum(3)
              ->newScheduledThreadPool();
    pool->submit(0,[]{
      usleep(200*1000);
    });
    usleep(100*1000);
    pool->shutdown();
    watch->start();
    pool->awaitTermination(50);
    long result = watch->stop();
    if(result < 50 || result > 55) {
      printf("---[ScheduledThreadPoolExecutor awaitTermination case3] [FAILED]--- ,result is %ld\n",result);
    }
    break;
  }

  while(1) {
    auto pool = createExecutorBuilder()
              ->setQueueSize(1)
              ->setMaxThreadNum(3)
              ->newScheduledThreadPool();
    pool->submit(0,[]{
    });
    usleep(100*1000);
    pool->shutdown();
    watch->start();
    pool->awaitTermination(50);
    long result = watch->stop();
    if(result < 0 || result > 5) {
      printf("---[ScheduledThreadPoolExecutor awaitTermination case4] [FAILED]--- ,result is %ld\n",result);
    }
    break;
  }

  while(1) {
    auto pool = createExecutorBuilder()
              ->setQueueSize(1)
              ->setMaxThreadNum(3)
              ->newScheduledThreadPool();
    pool->submit(0,[]{
      usleep(200*1000);
    });
    usleep(100*1000);
    pool->shutdown();
    watch->start();
    pool->awaitTermination(300);

    long result = watch->stop();
    if(result < 100 || result > 105) {
      printf("---[ScheduledThreadPoolExecutor awaitTermination case5] [FAILED]--- ,result is %ld\n",result);
    }
    break;
  }
  printf("---[ScheduledThreadPoolExecutor awaitTermination case100] [OK]--- \n");
}
