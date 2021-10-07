#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ThreadPoolExecutor.hpp"
#include "Integer.hpp"
#include "ExecutorBuilder.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

void testThreadLambdaSubmitTimeout() {
  TimeWatcher watcher = createTimeWatcher();
  while(1) {
    auto pool = createExecutorBuilder()
                ->setThreadNum(1)
                ->setQueueSize(1)
                ->newThreadPool();
    Future f1 = pool->submit([]{
      usleep(200*1000);
    });

    Future f2 = pool->submit([]{
    });

    watcher->start();
    Future f3 = pool->submitWithInTime(100,[]{

    });
    long result = watcher->stop();
    if(result < 100 || result > 105) {
      printf("---[ThreadPoolExecutor Submit_Timeout test1] [FAILED]---,result is %ld \n",result);
      break;
    }
    pool->shutdown();
    pool->awaitTermination();
    break;
  }

  while(1) {
    auto pool = createExecutorBuilder()
                ->setThreadNum(1)
                ->setQueueSize(1)
                ->newThreadPool();
    watcher->start();
    Future f1 = pool->submitWithInTime(100,[]{
      usleep(200*1000);
    });
    long result = watcher->stop();
    if(result < 0 || result > 5) {
      printf("---[ThreadPoolExecutor Submit_Timeout test2] [FAILED]---,result is %ld \n",result);
      break;
    }
    pool->shutdown();
    pool->awaitTermination();
    break;
  }

  while(1) {
    auto pool = createExecutorBuilder()
                ->setThreadNum(1)
                ->setQueueSize(1)
                ->newThreadPool();
    watcher->start();
    Future f1 = pool->submit([]{
      usleep(200*1000);
    });

    Future f2 = pool->submit([]{
    });

    watcher->start();
    Future f3 = pool->submitWithInTime(300,[]{

    });

    long result = watcher->stop();
    if(result < 200 || result > 205) {
      printf("---[ThreadPoolExecutor Submit_Timeout test3] [FAILED]---,result is %ld \n",result);
      break;
    }
    pool->shutdown();
    pool->awaitTermination();
    break;
  }

  printf("---[ThreadPoolExecutor Submit_Timeout test100] [OK]--- \n");
}
