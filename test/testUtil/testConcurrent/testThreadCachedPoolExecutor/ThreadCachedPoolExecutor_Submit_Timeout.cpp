#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ThreadCachedPoolExecutor.hpp"
#include "Integer.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "AutoClose.hpp"
#include "ExecutorBuilder.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

void CachedPoolSubmit_Timeout() {
  TimeWatcher watch = createTimeWatcher();

  while(1) {
    auto pool = createExecutorBuilder()
              ->setQueueSize(1)
              ->setMaxThreadNum(1)
              ->setTimeout(200)
              ->newCachedThreadPool();

    Future f1 = pool->submit([]{
      usleep(200*1000);
    });

    Future f2 = pool->submit([]{
    });

    watch->start();
    Future f3 = pool->submitWithInTime(100,[]{

    });
    long result = watch->stop();
    if(result < 100 || result > 105) {
      printf("---[TestCachedPoolExecutor Submit Timeout test1] [FAILED]---,result is %ld \n",result);
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
              ->setTimeout(200)
              ->newCachedThreadPool();

    Future f1 = pool->submit([]{
      usleep(300*1000);
    });

    Future f2 = pool->submit([]{
    });

    Thread t = createThread([&pool]{
        usleep(100*1000);
        pool->shutdown();
    });
    t->start();

    watch->start();
    Future f3 = pool->submitWithInTime(200,[]{
    });
    long result = watch->stop();
    if(result < 100 || result > 105) {
      printf("---[TestCachedPoolExecutor Submit Timeout test2] [FAILED]--- result is %ld\n",result);
      break;
    }

    pool->awaitTermination();
    break;
  }

  printf("---[TestCachedPoolExecutor Submit Timeout test100] [OK]--- \n");
}
