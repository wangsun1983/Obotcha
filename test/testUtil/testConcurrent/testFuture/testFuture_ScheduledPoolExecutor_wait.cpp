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

void testScheduledPoolExecutor_Wait() {
  TimeWatcher watcher = createTimeWatcher();

  while(1) {
      auto pool = createExecutorBuilder()
                ->setQueueSize(1)
                ->newScheduledThreadPool();
      int value = 100;
      Future f1 = pool->submit(200,[&value](){
        value = 222;
        st(TaskResult)::set(333);
      });
      watcher->start();
      f1->wait();
      long time = watcher->stop();
      if(time < 200 || time > 205) {
        printf("---[Future ScheduledThreadPool Wait case1 -------[FAILED] \n");
        break;
      }
      pool->shutdown();
      pool->awaitTermination();
      break;
  }

  while(1) {
    auto pool = createExecutorBuilder()
              ->setQueueSize(1)
              ->newScheduledThreadPool();

      int value = 100;
      Future f1 = pool->submit(200,[&value](){
        value = 222;
        st(TaskResult)::set(333);
      });

      watcher->start();
      int ret = f1->wait(100);
      long time = watcher->stop();

      if(time < 100 || time > 105) {
        printf("---[Future ScheduledThreadPool Wait case2 -------[FAILED] \n");
        break;
      }

      if(ret != -WaitTimeout) {
        printf("---[Future ScheduledThreadPool Wait case2_1 -------[FAILED] \n");
        break;
      }
      pool->shutdown();
      pool->awaitTermination();
      break;
  }

  while(1) {
    auto pool = createExecutorBuilder()
              ->setQueueSize(1)
              ->newScheduledThreadPool();

    int value = 100;
    Future f1 = pool->submit(200,[&value](){
      usleep(200*1000);
      value = 222;
      st(TaskResult)::set(333);
    });
    usleep(100);
    f1->cancel();
    watcher->start();
    int ret = f1->wait(100);
    long time = watcher->stop();
    if(time < 0 || time > 5) {
      printf("---[Future ScheduledThreadPool Wait case4 -------[FAILED] \n");
      break;
    }
    pool->shutdown();
    pool->awaitTermination();
    break;
  }

  while(1) {
    auto pool = createExecutorBuilder()
              ->setQueueSize(32)
              ->newScheduledThreadPool();

    CountDownLatch latch = createCountDownLatch(3);
    pool->submit(100,[]{
      usleep(100*1000);
    });

    pool->submit(100,[]{
      usleep(100*1000);
    });

    pool->submit(100,[]{
      usleep(100*1000);
    });

    Future f1 = pool->submit(200,[]{
      //
    });

    Future f2 = pool->submit(200,[]{
      //
    });

    Future f3 = pool->submit(200,[]{
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
    if(result < 195 || result > 205) {
      printf("---[Future ScheduledThreadPool Wait case5 -------[FAILED],result is %ld \n",result);
      break;
    }

    pool->shutdown();
    pool->awaitTermination();
    break;
  }

  while(1) {
    auto pool = createExecutorBuilder()
              ->setQueueSize(32)
              ->newScheduledThreadPool();
    pool->submit(100,[]{
      //TODO
    });

    Future f = pool->submit(100,[]{
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
    if(result < 0 || result > 15) {
      printf("---[Future ScheduledThreadPool Wait case6 -------[FAILED],result is %ld \n",result);
      break;
    }

    pool->awaitTermination();
    break;
  }

  printf("---[Future ScheduledThreadPool Wait case100 -------[OK] \n");
}
