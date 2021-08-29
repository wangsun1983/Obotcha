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
#include "CountDownLatch.hpp"

using namespace obotcha;

void testThreadPoolExecutor_Wait() {

  TimeWatcher watcher = createTimeWatcher();

  while(1) {
      auto pool = createExecutorBuilder()
                ->setThreadNum(1)
                ->newThreadPool();
      int value = 100;
      Future f1 = pool->submit([&value](){
        usleep(200*1000);
        value = 222;
        st(TaskResult)::set(333);
      });

      watcher->start();
      f1->wait();
      long time = watcher->stop();

      if(time < 200 || time > 205) {
        printf("---[Future ThreadPoolExecutor Wait case1 -------[FAILED] \n");
        break;
      }
      pool->shutdown();
      pool->awaitTermination();
      break;
  }

  while(1) {
      auto pool = createExecutorBuilder()
              ->setThreadNum(1)
              ->newThreadPool();
      int value = 100;
      Future f1 = pool->submit([&value](){
        usleep(200*1000);
        value = 222;
        st(TaskResult)::set(333);
      });

      watcher->start();
      int ret = f1->wait(100);
      long time = watcher->stop();

      if(time < 100 || time > 105) {
        printf("---[Future ThreadPoolExecutor Wait case2 -------[FAILED] \n");
        break;
      }

      if(ret != -WaitTimeout) {
        printf("---[Future ThreadPoolExecutor Wait case2_1 -------[FAILED] \n");
        break;
      }
      pool->shutdown();
      pool->awaitTermination();
      break;
  }

  while(1) {
    auto pool = createExecutorBuilder()->setThreadNum(1)->newThreadPool();
    int value = 100;
    Future f1 = pool->submit([&value](){
      usleep(200*1000);
      value = 222;
      st(TaskResult)::set(333);
    });
    usleep(100);
    f1->cancel();
    watcher->start();
    int ret = f1->wait(100);
    long time = watcher->stop();
    if(time < 95 || time > 105) {
      printf("---[Future ThreadPoolExecutor Wait case4 -------[FAILED] \n");
      break;
    }
    pool->shutdown();
    pool->awaitTermination();
    break;
  }

  while(1) {
    auto pool = createExecutorBuilder()
                ->setThreadNum(3)
                ->newThreadPool();
    CountDownLatch latch = createCountDownLatch(3);
    pool->submit([]{
      usleep(100*1000);
    });

    pool->submit([]{
      usleep(100*1000);
    });

    pool->submit([]{
      usleep(100*1000);
    });

    Future f1 = pool->submit([]{
      //
    });

    Future f2 = pool->submit([]{
      //
    });

    Future f3 = pool->submit([]{
      //
    });

    Thread t1 = createThread([&f1,&latch]{
      f1->wait();
      latch->countDown();
    });
    t1->start();

    Thread t2 = createThread([&f2,&latch]{
      f2->wait();
      latch->countDown();
    });
    t2->start();

    Thread t3 = createThread([&f3,&latch]{
      f3->wait();
      latch->countDown();
    });
    t3->start();

    watcher->start();
    latch->await();
    long result = watcher->stop();
    if(result < 95 || result > 105) {
      printf("---[Future ThreadPoolExecutor Wait case5 -------[FAILED],result is %ld \n",result);
      break;
    }

    pool->shutdown();
    pool->awaitTermination();
    break;
  }

  while(1) {
    auto pool = createExecutorBuilder()->setThreadNum(1)->newThreadPool();
    pool->submit([]{
      usleep(100*1000);
    });

    Future f = pool->submit([]{
      //TODO
    });

    Thread t = createThread([&pool]{
      usleep(10*1000);
      pool->shutdown();
    });
    t->start();

    watcher->start();
    f->wait();
    long result = watcher->stop();
    if(result < 10 || result > 15) {
      printf("---[Future ThreadPoolExecutor Wait case6 -------[FAILED],result is %ld \n",result);
      break;
    }

    pool->awaitTermination();
    break;
  }

  printf("---[Future ThreadPoolExecutor Wait case100 -------[OK] \n");
}
