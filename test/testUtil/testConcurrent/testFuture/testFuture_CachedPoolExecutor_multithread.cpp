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
#include "CountDownLatch.hpp"

using namespace obotcha;

void testCachedPoolExecutor_Multithread() {
  while(1) {
    auto pool = createExecutorBuilder()
              ->setMaxThreadNum(32)
              ->newCachedThreadPool();

    CountDownLatch latch = createCountDownLatch(32*1024);
    ArrayList<Future> lists = createArrayList<Future>();
    for(int i = 0;i<32*1024;i++) {
      Future t = pool->submit([&latch,i]{
        st(TaskResult)::set(i);
        latch->countDown();
      });
      lists->add(t);
    }

    latch->await();
    auto iterator = lists->getIterator();
    int sum = 0;
    while(iterator->hasValue()) {
      sum += iterator->getValue()->getResult<int>();
      iterator->next();
    }

    int expectSum = 0;
    for(int i = 0;i <32*1024;i++) {
      expectSum += i;
    }

    if(sum != expectSum) {
      printf("---[Future CachedPoolExecutor Multithread case1 -------[FAILED] \n");
      break;
    }

    pool->shutdown();
    pool->awaitTermination();
    break;
  }
  printf("---[Future CachedPoolExecutor Multithread case100 -------[OK] \n");
}
