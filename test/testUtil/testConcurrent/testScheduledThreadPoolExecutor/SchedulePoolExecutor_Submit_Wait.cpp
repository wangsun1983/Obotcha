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

void testSubmitWait() {
  TimeWatcher watch = createTimeWatcher();

  while(1) {
    auto pool = createExecutorBuilder()
              ->setQueueSize(1)
              ->setMaxThreadNum(3)
              ->newScheduledThreadPool();
    printf("trace1 \n");
    auto f1 = pool->schedule(100,[]{

    });
    printf("trace2 \n");
    watch->start();
    auto f2 = pool->schedule(100,[]{

    });
    printf("trace3 \n");
    long result = watch->stop();

    if(result < 0 || result > 105) {
      printf("---[ScheduledThreadPoolExecutor SubmitWait case1] [FAILED]--- \n");
      break;
    }

    break;
  }

  printf("---[ScheduledThreadPoolExecutor SubmitWait case100] [OK]--- \n");
}
