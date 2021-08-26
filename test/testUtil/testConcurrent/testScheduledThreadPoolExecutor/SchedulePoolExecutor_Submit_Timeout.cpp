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

using namespace obotcha;

void testSubmitTimeout() {
  TimeWatcher watch = createTimeWatcher();

  while(1) {
    auto pool = createExecutorBuilder()
              ->setQueueSize(1)
              ->setMaxThreadNum(3)
              ->newScheduledThreadPool();
    auto f1 = pool->submit(200,[]{

    });

    watch->start();
    auto f2 = pool->submitWithInTime(50,100,[]{

    });

    long result = watch->stop();

    if(result < 0 || result > 55) {
      printf("---[ScheduledThreadPoolExecutor SubmitTimeout case1] [FAILED]--- \n");
      break;
    }
    pool->shutdown();
    pool->awaitTermination();
    break;
  }

  while(1) {
    auto pool = createExecutorBuilder()
              ->setQueueSize(2)
              ->setMaxThreadNum(3)
              ->newScheduledThreadPool();

    auto f1 = pool->submit(200,[]{

    });

    watch->start();
    auto f2 = pool->submitWithInTime(50,100,[]{

    });

    long result = watch->stop();
    if(result < 0 || result > 5) {
      printf("---[ScheduledThreadPoolExecutor SubmitTimeout case2] [FAILED]--- \n");
      break;
    }
    pool->shutdown();
    pool->awaitTermination();
    break;
  }

  printf("---[ScheduledThreadPoolExecutor SubmitTimeout case100] [OK]--- \n");
}
