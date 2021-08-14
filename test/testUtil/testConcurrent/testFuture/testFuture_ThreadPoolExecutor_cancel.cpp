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

      Future f2 = pool->submit([](){
        st(TaskResult)::set(100);
      });
      usleep(100*1000);
      f1->cancel();
      f2->cancel();

      if(value != 222) {
        printf("---[Future ThreadPoolExecutor Cancel case1 -------[FAIL] \n");
        break;
      }

      bool isException = false;
      try {
        int v = f1->getResult<int>();
      } catch(...) {
        isException = true;
      }

      if(!isException) {
        printf("---[Future ThreadPoolExecutor Cancel case2 -------[FAIL] \n");
        break;
      }

      break;
  }

  printf("---[Future ThreadPoolExecutor Cancel case100 -------[OK] \n");
}
