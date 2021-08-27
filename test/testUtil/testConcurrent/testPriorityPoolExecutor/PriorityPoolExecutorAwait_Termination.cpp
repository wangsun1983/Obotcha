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

void testAwaitTermination() {
  TimeWatcher watch = createTimeWatcher();
  while(1) {
    auto pool = createExecutorBuilder()
              ->setQueueSize(1)
              ->setThreadNum(1)
              ->newPriorityThreadPool();

    pool->submit(st(Executor)::Medium,[]{
      usleep(100*1000);
    });

    pool->submit(st(Executor)::Medium,[]{
      usleep(100*1000);
    });

    pool->shutdown();
    watch->start();
    pool->awaitTermination();
    long result = watch->stop();

    if(result < 100 || result > 105) {
      printf("---[TestPriorityPoolExecutor Await Termination Test case1] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    auto pool = createExecutorBuilder()
              ->setQueueSize(1)
              ->setThreadNum(1)
              ->newPriorityThreadPool();

    pool->submit(st(Executor)::Medium,[]{
      usleep(200*1000);
    });
    usleep(10);

    pool->shutdown();
    watch->start();
    pool->awaitTermination(100);
    long result = watch->stop();

    if(result < 100 || result > 105) {
      printf("---[TestPriorityPoolExecutor Await Termination Test case2] [FAILED]---,result is %ld \n",result);
      break;
    }
    break;
  }

  printf("---[TestPriorityPoolExecutor Await Termination Test case100] [OK]--- \n");

}
