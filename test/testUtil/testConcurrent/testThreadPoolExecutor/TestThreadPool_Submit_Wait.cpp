#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "System.hpp"
#include "ExecutorBuilder.hpp"
#include "Error.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

void testThreadPoolSubmit_Wait() {
  auto pool = createExecutorBuilder()
              ->setThreadNum(1)
              ->setQueueSize(1)
              ->newThreadPool();
  TimeWatcher watcher = createTimeWatcher();

  while(1) {
    Future f1 = pool->submit([]{
      usleep(200*1000);
    });

    Future f2 = pool->submit([]{
    });

    watcher->start();
    Future f3 = pool->submit([]{
    });
    long value = watcher->stop();
    if(value < 0 || value > 205) {
      printf("---[ThreadPoolExecutor Submit_Wait test1 value is %ld] [FAILED]--- \n",value);
      break;
    }
    break;
  }

  while(1) {
    Future f1 = pool->submit([]{
      usleep(200*1000);
    });

    Future f2 = pool->submit([]{
      usleep(200*1000);
    });

    watcher->start();
    Future f3 = pool->submit([]{
    });
    long value = watcher->stop();
    if(value < 0 || value > 405) {
      printf("---[ThreadPoolExecutor Submit_Wait test2 value is %ld] [FAILED]--- \n",value);
      break;
    }
    break;
  }

  while(1) {
    auto pool2 = createExecutorBuilder()
                ->setThreadNum(2)
                ->setQueueSize(1)
                ->newThreadPool();

    Future f1 = pool2->submit([]{
      usleep(200*1000);
    });

    Future f2 = pool2->submit([]{
      usleep(200*1000);
    });

    watcher->start();
    Future f3 = pool2->submit([]{
    });
    long value = watcher->stop();

    if(value < 0 || value > 5) {
      printf("---[ThreadPoolExecutor Submit_Wait test3 value is %ld] [FAILED]--- \n",value);
      break;
    }

    pool2->shutdown();
    pool2->awaitTermination();
    break;
  }

  while(1) {
    auto pool2 = createExecutorBuilder()
                ->setThreadNum(2)
                ->setQueueSize(1)
                ->newThreadPool();

    Future f1 = pool2->submit([]{
      usleep(200*1000);
    });

    Future f2 = pool2->submit([]{
      usleep(200*1000);
    });

    Future f3 = pool2->submit([]{
      usleep(200*1000);
    });

    watcher->start();
    Future f4 = pool2->submit([]{
    });
    long value = watcher->stop();

    if(value < 0 || value > 205) {
      printf("---[ThreadPoolExecutor Submit_Wait test4 value is %ld] [FAILED]--- \n",value);
      break;
    }

    pool2->shutdown();
    pool2->awaitTermination();
    break;
  }

  while(1) {
    auto pool2 = createExecutorBuilder()
                ->setThreadNum(1)
                ->setQueueSize(1)
                ->newThreadPool();
    Future f1 = pool2->submit([]{
      usleep(200*1000);
    });

    Future f2 = pool2->submit([]{
    });

    pool2->shutdown();
    watcher->start();
    f2->wait();
    long result = watcher->stop();
    if(result > 5 || result < 0) {
      printf("---[ThreadPoolExecutor Submit_Wait test5 result is %ld] [FAILED]--- \n",result);
      break;
    }
    pool2->awaitTermination();
    break;
  }

  while(1) {
    auto pool2 = createExecutorBuilder()
                ->setThreadNum(1)
                ->setQueueSize(1)
                ->newThreadPool();
    Future f1 = pool2->submit([]{
      usleep(200*1000);
    });

    pool2->shutdown();
    watcher->start();
    Future f2 = pool2->submit([]{
    });

    long result = watcher->stop();
    if(result > 5 || result < 0) {
      printf("---[ThreadPoolExecutor Submit_Wait test6 result is %ld] [FAILED]--- \n",result);
      break;
    }
    pool2->awaitTermination();
    break;
  }

  while(1) {
    auto pool2 = createExecutorBuilder()
                ->setThreadNum(1)
                ->setQueueSize(2)
                ->newThreadPool();
    Future f1 = pool2->submit([]{
      usleep(200*1000);
    });

    watcher->start();
    Future f2 = pool2->submit([]{
    });
    long result = watcher->stop();
    if(result > 5 || result < 0) {
      printf("---[ThreadPoolExecutor Submit_Wait test7 result is %ld] [FAILED]--- \n",result);
      break;
    }

    watcher->start();
    Future f3 = pool2->submit([]{
    });
    result = watcher->stop();
    if(result > 5 || result < 0) {
      printf("---[ThreadPoolExecutor Submit_Wait test8 result is %ld] [FAILED]--- \n",result);
      break;
    }

    watcher->start();
    Future f4 = pool2->submit([]{
    });
    result = watcher->stop();
    if(result > 205 || result < 200) {
      printf("---[ThreadPoolExecutor Submit_Wait test9 result is %ld] [FAILED]--- \n",result);
      break;
    }
    pool2->shutdown();
    pool2->awaitTermination();
    break;
  }

  while(1) {
    int sum = 0;
    watcher->start();
    Future f1 =  pool->submit([&sum]{
      usleep(200*1000);
      sum++;
    });

    Future f2 =  pool->submit([&sum]{
      usleep(200*1000);
      sum++;
    });

    Future f3 =  pool->submit([&sum]{
      usleep(200*1000);
      sum++;
    });

    f3->wait();
    long result = watcher->stop();
    if(result > 605 || result < 600) {
      printf("---[ThreadPoolExecutor Submit_Wait test10 result is %ld] [FAILED]--- \n",result);
      break;
    }
    break;
  }

  pool->shutdown();
  pool->awaitTermination();

  printf("---[ThreadPoolExecutor Submit_Wait test100] [OK]--- \n");
}
