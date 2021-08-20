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

void CachedPoolSubmit_Wait() {
  auto pool = createExecutorBuilder()
            ->setQueueSize(1)
            ->setMaxThreadNum(1)
            ->setTimeout(200)
            ->newCachedThreadPool();
  TimeWatcher watch = createTimeWatcher();

  while(1) {
    Future f1 = pool->submit([]{
      usleep(100*1000);
    });

    Future f2 = pool->submit([]{
    });

    watch->start();
    Future f3 = pool->submit([]{
    });
    long result = watch->stop();
    if(result < 100 || result > 105) {
      printf("---[TestCachedPoolExecutor SubmitWait test1] [FAILED]--- \n");
      break;
    }

    usleep(250*1000);
    if(pool->getThreadsNum() != 0) {
      printf("---[TestCachedPoolExecutor SubmitWait test2] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    Future f1 = pool->submit([]{
      usleep(100*1000);
    });

    Future f2 = pool->submit([]{
      usleep(100*1000);
    });

    watch->start();
    Future f3 = pool->submit([]{
    });
    long result = watch->stop();
    if(result < 100 || result > 105) {
      printf("---[TestCachedPoolExecutor SubmitWait test3] [FAILED]---,result is %ld \n",result);
      break;
    }

    watch->start();
    f3->wait();
    result = watch->stop();
    if(result < 100 || result > 105) {
      printf("---[TestCachedPoolExecutor SubmitWait test4] [FAILED]---,result is %ld \n",result);
      break;
    }

    usleep(250*1000);
    if(pool->getThreadsNum() != 0) {
      printf("---[TestCachedPoolExecutor SubmitWait test5] [FAILED]--- \n");
      break;
    }
    break;
  }

  pool->shutdown();
  pool->awaitTermination();
  printf("---[TestCachedPoolExecutor SubmitWait test100] [OK]--- \n");
}
