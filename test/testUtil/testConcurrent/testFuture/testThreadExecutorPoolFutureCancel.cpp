#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ExecutorService.hpp"
#include "Integer.hpp"
#include "Executors.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Math.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(TestCancelTask) IMPLEMENTS(Runnable){
public:
  static int count;
  void run() {
    count++;
    sleep(1);
  }
};

int st(TestCancelTask)::count = 0;

int testThreadExecutorPoolFutureCancel() {
    //case1
    while(1) {
      TestCancelTask task = createTestCancelTask();
      ExecutorService pool = st(Executors)::newFixedThreadPool(1);
      Future f1 = pool->submit(task);
      Future f2 = pool->submit(task);
      f2->cancel();
      sleep(3);
      if(st(TestCancelTask)::count != 1) {
        printf("testThreadExecutorPoolFutureCancel case1 -------[FAIL] \n");
        pool->shutdown();
        break;
      }

      long trace1 = st(System)::currentTimeMillis();
      f2->wait(1000);
      long interval = st(System)::currentTimeMillis() - trace1;
      if(interval > 5) {
        printf("testThreadExecutorPoolFutureCancel case2 -------[FAIL] \n");
        pool->shutdown();
        break;
      }

      printf("testThreadExecutorPoolFutureCancel case3 -------[OK] \n");
      break;
    }

    //case2
    while(1) {
      TestCancelTask task = createTestCancelTask();
      ExecutorService pool = st(Executors)::newFixedThreadPool(1);
      Future f1 = pool->submit(task);
      Future f2 = pool->submit(task);
      pool->shutdown();
      f1->cancel();
      f2->cancel();

      long trace1 = st(System)::currentTimeMillis();
      f2->wait(1000);
      long interval = st(System)::currentTimeMillis() - trace1;
      if(interval > 5) {
        printf("testThreadExecutorPoolFutureCancel case4 -------[FAIL] \n");
        break;
      }

      printf("testThreadExecutorPoolFutureCancel case5 -------[OK] \n");
      break;
    }
}
