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

using namespace obotcha;

void testThreadPoolExecutor_Cancel() {
  auto pool = createExecutorBuilder()
              ->setThreadNum(1)
              ->newThreadPool();
  while(1) {
      int value = 100;
      Future f1 = pool->submit([&value](){
        usleep(200*1000);
        value = 222;
        st(TaskResult)::set(333);
      });

      Future f2 = pool->submit([](){
        st(TaskResult)::set(100);
      });

      usleep(100*1000);
      f1->cancel();
      f2->cancel();
      usleep(150*1000);
      if(value != 222) {
        printf("---[Future ThreadPoolExecutor Cancel case2 -------[FAIL],value is %d \n",value);
        break;
      }

      bool isException = false;
      try {
        int v = f2->getResult<int>();
      } catch(...) {
        isException = true;
      }

      if(!isException) {
        printf("---[Future ThreadPoolExecutor Cancel case3 -------[FAIL] \n");
        break;
      }
      break;
  }

  while(1) {
    int value = 123;
    Future f1 = pool->submit([&value](){
      value = 222;
      st(TaskResult)::set(333);
    });
    usleep(100*1000);
    f1->cancel();

    if(value != 222) {
      printf("---[Future ThreadPoolExecutor Cancel case4 -------[FAIL] \n");
      break;
    }

    if(f1->getResult<int>() != 333) {
      printf("---[Future ThreadPoolExecutor Cancel case5 -------[FAIL] \n");
      break;
    }
    break;
  }

  pool->shutdown();
  pool->awaitTermination();

  printf("---[Future ThreadPoolExecutor Cancel case100 -------[OK] \n");
}
