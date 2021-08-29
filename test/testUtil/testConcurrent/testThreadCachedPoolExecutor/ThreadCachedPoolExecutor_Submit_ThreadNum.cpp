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

void CachedPoolSubmit_ThreadNum() {
  auto pool = createExecutorBuilder()
            ->setQueueSize(1)
            ->setMaxThreadNum(3)
            ->setTimeout(200)
            ->newCachedThreadPool();
  TimeWatcher watch = createTimeWatcher();

  while(1) {
    Future f1 = pool->submit([]{
      usleep(100*1000);
    });
    usleep(1000);
    if(pool->getThreadsNum() != 1 || pool->getTasksNum() != 0) {
      printf("---[TestCachedPoolExecutor ThreadNum test1] [FAILED]--- threads is %d,tasks is %d \n",pool->getThreadsNum(),pool->getTasksNum());
      break;
    }

    Future f2 = pool->submit([]{
      usleep(100*1000);
    });
    usleep(1000);
    if(pool->getThreadsNum() != 2 || pool->getTasksNum() != 0) {
      printf("---[TestCachedPoolExecutor ThreadNum test2] [FAILED]--- \n");
      break;
    }

    Future f3 = pool->submit([]{
      usleep(100*1000);
    });
    usleep(1000);
    if(pool->getThreadsNum() != 3 || pool->getTasksNum() != 0) {
      printf("---[TestCachedPoolExecutor ThreadNum test3] [FAILED]--- \n");
      break;
    }

    Future f4 = pool->submit([]{
      usleep(100*1000);
    });
    if(pool->getThreadsNum() != 3 || pool->getTasksNum() != 1) {
      printf("---[TestCachedPoolExecutor ThreadNum test4] [FAILED]--- \n");
      break;
    }

    usleep(405*1000);
    if(pool->getThreadsNum() != 0 || pool->getTasksNum() != 0) {
      printf("---[TestCachedPoolExecutor ThreadNum test5] [FAILED]--- threads is %d,tasks is %d \n",pool->getThreadsNum(),pool->getTasksNum());
      break;
    }

    break;
  }

  while(1) {
    for(int i = 0;i < 1024;i++) {
      Future f1 = pool->submit([]{

      });
    }
    usleep(205*1000);
    if(pool->getThreadsNum() != 0 || pool->getTasksNum() != 0) {
      printf("---[TestCachedPoolExecutor ThreadNum test6] [FAILED]--- threads is %d,tasks is %d \n",pool->getThreadsNum(),pool->getTasksNum());
      break;
    }

    break;
  }

  while(1) {
    auto pool2 = createExecutorBuilder()
              ->setQueueSize(12)
              ->setMaxThreadNum(12)
              ->setTimeout(100)
              ->newCachedThreadPool();
    for(int i = 0;i < 1024;i++) {
      Future f1 = pool2->submit([]{

      });
    }
    usleep(105*1000);
    if(pool2->getThreadsNum() != 0 || pool2->getTasksNum() != 0) {
      printf("---[TestCachedPoolExecutor ThreadNum test7] [FAILED]--- threads is %d,tasks is %d \n",pool2->getThreadsNum(),pool2->getTasksNum());
      break;
    }

    pool2->shutdown();
    pool2->awaitTermination();
    break;
  }

  while(1) {
    auto pool2 = createExecutorBuilder()
              ->setQueueSize(32)
              ->setMaxThreadNum(12)
              ->setTimeout(100)
              ->newCachedThreadPool();
    for(int i = 0;i < 1024;i++) {
      Future f1 = pool2->submit([]{
        usleep(1);
      });
    }
    usleep(150*1000);
    if(pool2->getThreadsNum() != 0 || pool2->getTasksNum() != 0) {
      printf("---[TestCachedPoolExecutor ThreadNum test8] [FAILED]--- threads is %d,tasks is %d \n",pool2->getThreadsNum(),pool2->getTasksNum());
      break;
    }

    pool2->shutdown();
    pool2->awaitTermination();
    break;
  }

  while(1) {
    auto pool2 = createExecutorBuilder()
              ->setQueueSize(1024*4)
              ->setMaxThreadNum(12)
              ->setTimeout(100)
              ->newCachedThreadPool();
    for(int i = 0;i < 1024*4;i++) {
      Future f1 = pool2->submit([]{
        usleep(1);
      });
    }

    if(pool2->getThreadsNum() != 12) {
      printf("---[TestCachedPoolExecutor ThreadNum test9] [FAILED]--- threads is %d,tasks is %d \n",pool2->getThreadsNum(),pool2->getTasksNum());
      break;
    }

    usleep(150*1000);
    if(pool2->getThreadsNum() != 0 || pool2->getTasksNum() != 0) {
      printf("---[TestCachedPoolExecutor ThreadNum test10] [FAILED]--- threads is %d,tasks is %d \n",pool2->getThreadsNum(),pool2->getTasksNum());
      break;
    }

    pool2->shutdown();
    pool2->awaitTermination();
    break;
  }

  pool->shutdown();
  pool->awaitTermination();
  printf("---[TestCachedPoolExecutor ThreadNum test100] [OK]--- \n");
}
