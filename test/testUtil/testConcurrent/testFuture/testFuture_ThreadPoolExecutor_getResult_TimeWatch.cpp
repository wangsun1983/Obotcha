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

void testThreadPoolExecutor_GetResult_TimeWatch() {
  auto pool = createExecutorBuilder()
              ->setThreadNum(1)
              ->newThreadPool();

  TimeWatcher watcher = createTimeWatcher();
  while(1) {
      Future f1 = pool->submit([]{
          usleep(200*1000);
          st(TaskResult)::set(111);
      });
      watcher->start();
      int ret = f1->getResult<int>();
      long interval = watcher->stop();
      if(interval<200 || interval > 205) {
        printf("---[Future ThreadPoolExecutor GetResult TimeWatch case1 -------[FAILED] interval is %ld \n",interval);
        break;
      }

      if(ret != 111) {
        printf("---[Future ThreadPoolExecutor GetResult TimeWatch case2 -------[FAILED] \n");
        break;
      }
      break;
  }

  while(1) {
      Future f1 = pool->submit([]{
          usleep(200*1000);
      });
      watcher->start();
      bool isException = false;
      try {
        int ret = f1->getResult<int>();
      } catch(...) {

      }
      long interval = watcher->stop();
      if(interval<200 || interval > 205) {
        printf("---[Future ThreadPoolExecutor GetResult TimeWatch case3 -------[FAILED] interval is %ld \n",interval);
        break;
      }

      break;
  }

  while(1) {
      Future f1 = pool->submit([]{
          usleep(200*1000);
      });
      watcher->start();
      bool isException = false;
      try {
        int ret = f1->getResult<int>(100);
      } catch(...) {
        isException = true;
      }

      long interval = watcher->stop();
      if(!isException || interval<100 || interval > 105) {
        printf("---[Future ThreadPoolExecutor GetResult TimeWatch case4 -------[FAILED] interval is %ld \n",interval);
        break;
      }

      break;
  }

  while(1) {
      Future f1 = pool->submit([]{
          usleep(200*1000);
          st(TaskResult)::set(123);
      });
      watcher->start();
      bool isException = false;
      int ret = 0;

      try {
        ret = f1->getResult<int>(100);
      } catch(...) {
        isException = true;
      }

      long interval = watcher->stop();
      if(isException || interval<100 || interval > 105 || ret != 123) {
        printf("---[Future ThreadPoolExecutor GetResult TimeWatch case5 -------[FAILED] interval is %ld \n",interval);
        break;
      }

      break;
  }

  pool->shutdown();
  pool->awaitTermination();

  printf("---[Future ThreadPoolExecutor GetResult TimeWatch case100 -------[OK] \n");
}
