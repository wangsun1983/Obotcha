#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ExecutorBuilder.hpp"
#include "Integer.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Math.hpp"
#include "TaskResult.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

DECLARE_CLASS(InterruptTestData) {
public:
  _InterruptTestData(int p) {
    v = p;
  }

  int v;
};

void testThreadPoolExecutor_GetResult_Interrupt() {
  TimeWatcher watcher = createTimeWatcher();
  while(1) {
    auto pool = createExecutorBuilder()
                ->setThreadNum(1)
                ->newThreadPool();

    Future f1 = pool->submit([]{
      usleep(100*1000);
      st(TaskResult)::set(100);
    });

    usleep(10*1000);
    pool->shutdown();

    watcher->start();
    int v = f1->getResult<int>();
    long result = watcher->stop();

    if(result < 85 || result > 95) {
      printf("---[Future ThreadPoolExecutor GetResult Interrupt case1 -------[FAILED] ,result is %ld\n",result);
      break;
    }

    if(v != 100) {
      printf("---[Future ThreadPoolExecutor GetResult Interrupt case2 -------[FAILED] ,v is %d\n",v);
      break;
    }

    break;
  }

  while(1) {
    auto pool = createExecutorBuilder()
                ->setThreadNum(1)
                ->newThreadPool();
    pool->submit([] {
      usleep(100*1000);
    });

    Future f1 = pool->submit([]{
      st(TaskResult)::set(createInterruptTestData(123));
    });

    Thread t = createThread([&pool]{
      usleep(10*1000);
      pool->shutdown();
    });
    t->start();

    watcher->start();
    InterruptTestData v = nullptr;
    bool isException = false;
    try {
      v = f1->getResult<InterruptTestData>();
    } catch(...) {
      isException = true;
    }

    long result = watcher->stop();
    if(result < 5 || result > 15) {
      printf("---[Future ThreadPoolExecutor GetResult Interrupt case3 -------[FAILED] ,result is %ld\n",result);
      break;
    }

    if(v != nullptr) {
      printf("---[Future ThreadPoolExecutor GetResult Interrupt case4 -------[FAILED]\n");
      break;
    }

    if(!isException) {
      printf("---[Future ThreadPoolExecutor GetResult Interrupt case4_1 -------[FAILED]\n");
      break;
    }

    pool->awaitTermination();
    break;
  }

  while(1) {
    auto pool = createExecutorBuilder()
                ->setThreadNum(1)
                ->newThreadPool();
    pool->submit([] {
      usleep(100*1000);
    });

    Future f1 = pool->submit([]{
      st(TaskResult)::set(123);
    });

    Thread t = createThread([&pool]{
      usleep(10*1000);
      pool->shutdown();
    });
    t->start();

    watcher->start();
    bool isException = false;
    try {
      auto v = f1->getResult<int>();
    } catch(...) {
      isException = true;
    }

    long result = watcher->stop();
    if(result < 5 || result > 15) {
      printf("---[Future ThreadPoolExecutor GetResult Interrupt case5 -------[FAILED] ,result is %ld\n",result);
      break;
    }

    if(!isException) {
      printf("---[Future ThreadPoolExecutor GetResult Interrupt case6 -------[FAILED]\n");
      break;
    }

    pool->awaitTermination();
    break;
  }

  printf("---[Future ThreadPoolExecutor GetResult Interrupt case100 -------[OK] \n");
}
