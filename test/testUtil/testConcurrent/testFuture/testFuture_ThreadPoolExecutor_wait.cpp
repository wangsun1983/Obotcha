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

void testThreadPoolExecutor_Wait() {
  auto pool = createExecutorBuilder()
              ->setThreadNum(1)
              ->newThreadPool();
  TimeWatcher watcher = createTimeWatcher();

  while(1) {
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

      break;
  }

  while(1) {
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

      break;
  }

  while(1) {
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

      if(ret != -AlreadyComplete) {
        printf("---[Future ThreadPoolExecutor Wait case3 -------[FAILED] \n");
        break;
      }

      if(time > 5) {
        printf("---[Future ThreadPoolExecutor Wait case4 -------[FAILED] \n");
        break;
      }

      break;
  }

  pool->shutdown();
  pool->awaitTermination();

  printf("---[Future ThreadPoolExecutor Wait case100 -------[OK] \n");
}
