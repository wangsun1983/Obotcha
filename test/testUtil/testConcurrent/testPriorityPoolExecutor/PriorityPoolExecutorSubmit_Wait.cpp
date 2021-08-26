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

using namespace obotcha;

void testSubmitWait() {
  TimeWatcher watch = createTimeWatcher();
  while(1) {
    auto pool = createExecutorBuilder()
              ->setQueueSize(1)
              ->setMaxThreadNum(1)
              ->newPriorityThreadPool();

    pool->submit(st(Executor)::Medium,[]{
      usleep(100*1000);
    });

    pool->submit(st(Executor)::Medium,[]{
      usleep(100*1000);
    });

    watch->start();
    pool->submit(st(Executor)::Medium,[]{

    });
    long result = watch->stop();
    if(result < 100 || result > 105) {
      printf("---[TestPriorityPoolExecutor SubmitWait Test case1] [FAILED]--- result is %ld\n",result);
      break;
    }

    pool->shutdown();
    pool->awaitTermination();
    break;
  }

  while(1) {
    auto pool = createExecutorBuilder()
              ->setQueueSize(1)
              ->setMaxThreadNum(1)
              ->newPriorityThreadPool();

    pool->submit(st(Executor)::Medium,[]{
      usleep(100*1000);
    });

    watch->start();
    pool->submit(st(Executor)::High,[]{

    });
    long result = watch->stop();
    if(result < 0 || result > 5) {
      printf("---[TestPriorityPoolExecutor SubmitWait Test case2] [FAILED]--- result is %ld\n",result);
      break;
    }

    pool->shutdown();
    pool->awaitTermination();
    break;
  }
  printf("---[TestPriorityPoolExecutor SubmitWait Test case100] [OK]--- \n");

}
