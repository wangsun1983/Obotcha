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

void CachedPoolSubmit_AwaitTermination() {
  TimeWatcher watch = createTimeWatcher();

  while(1) {
    auto pool = createExecutorBuilder()
              ->setQueueSize(1)
              ->setMaxThreadNum(3)
              ->setTimeout(200)
              ->newCachedThreadPool();

    Future f1 = pool->submit([]{
      usleep(100*1000);
    });

    pool->shutdown();
    watch->start();
    pool->awaitTermination();
    long result = watch->stop();
    if(result < 100 || result > 105) {
      printf("---[TestCachedPoolExecutor AwaitTermination test1] [FAILED]--- \n");
      break;
    }
    break;
  }
  
  printf("---[TestCachedPoolExecutor AwaitTermination test100] [OK]--- \n");
}
