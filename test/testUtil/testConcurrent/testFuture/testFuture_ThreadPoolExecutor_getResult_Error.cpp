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

void testThreadPoolExecutor_GetResult_Error() {
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

      bool isException = false;
      try {
        f1->getResult<bool>();
      } catch(...) {
        isException = true;
      }

      if(!isException) {
        printf("---[Future ThreadPoolExecutor GetResult Error case1 -------[FAILED] \n");
        break;
      }
      break;
  }

  while(1) {
      int value = 100;
      Future f1 = pool->submit([&value](){
        usleep(200*1000);
        value = 222;
        st(TaskResult)::set(createInteger(100));
      });

      int result = f1->getResult<int>();

      if(result != 100 || value != 222) {
        printf("---[Future ThreadPoolExecutor GetResult Error case2 -------[FAILED] \n");
        break;
      }
      break;
  }

  pool->shutdown();
  pool->awaitTermination();

  printf("---[Future ThreadPoolExecutor GetResult Error case100 -------[OK] \n");
}
