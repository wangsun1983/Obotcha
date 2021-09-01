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

void testScheduledPoolExecutor_Cancel() {
  auto pool = createExecutorBuilder()
            ->setQueueSize(32)
            ->newScheduledThreadPool();

  while(1) {
      int value = 100;
      Future f1 = pool->submit(200,[&value](){
        value = 222;
        st(TaskResult)::set(333);
      });

      Future f2 = pool->submit(0,[](){
        st(TaskResult)::set(100);
      });

      usleep(100*1000);
      f1->cancel();
      f2->cancel();
      usleep(150*1000);
      if(value == 222) {
        printf("---[Future ScheduledPoolExecutor Cancel case2 -------[FAIL],value is %d \n",value);
        break;
      }

      bool isException = false;
      int v = f2->getResult<int>();

      if(v != 100) {
        printf("---[Future ScheduledPoolExecutor Cancel case3 -------[FAIL] \n");
        break;
      }
      break;
  }

  while(1) {
    int value = 123;
    Future f1 = pool->submit(0,[&value](){
      usleep(200*100);
      value = 222;
      st(TaskResult)::set(333);
    });
    usleep(10*1000);
    f1->cancel();
    usleep(200*1000);
    if(value != 222) {
      printf("---[Future ScheduledPoolExecutor Cancel case4 -------[FAIL] \n");
      break;
    }

    if(f1->getResult<int>() != 333) {
      printf("---[Future ScheduledPoolExecutor Cancel case5 -------[FAIL] \n");
      break;
    }
    break;
  }

  pool->shutdown();
  pool->awaitTermination();

  printf("---[Future ScheduledPoolExecutor Cancel case100 -------[OK] \n");
}
