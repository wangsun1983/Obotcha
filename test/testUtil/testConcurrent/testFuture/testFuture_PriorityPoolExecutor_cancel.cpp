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

void testPriorityPoolExecutor_Cancel() {

  while(1) {
    auto pool = createExecutorBuilder()
                ->setThreadNum(1)
                ->newPriorityThreadPool();

      int value = 100;
      Future f1 = pool->submit(st(Executor)::High,[&value](){
        usleep(200*1000);
        value = 222;
        st(TaskResult)::set(333);
      });

      Future f2 = pool->submit(st(Executor)::High,[](){
        st(TaskResult)::set(100);
      });

      usleep(100*1000);
      f1->cancel();
      f2->cancel();
      usleep(150*1000);
      if(value != 222) {
        printf("---[Future PriorityPoolExecutor Cancel case2 -------[FAIL],value is %d \n",value);
        break;
      }

      bool isException = false;
      try {
        int v = f2->getResult<int>();
      } catch(...) {
        isException = true;
      }

      if(!isException) {
        printf("---[Future PriorityPoolExecutor Cancel case3 -------[FAIL] \n");
        break;
      }
      pool->shutdown();
      pool->awaitTermination();
      break;
  }

  while(1) {
    auto pool = createExecutorBuilder()
                ->setThreadNum(1)
                ->newPriorityThreadPool();

    int value = 123;
    Future f1 = pool->submit(st(Executor)::High,[&value](){
      value = 222;
      st(TaskResult)::set(333);
    });
    usleep(100*1000);
    f1->cancel();

    if(value != 222) {
      printf("---[Future PriorityPoolExecutor Cancel case4 -------[FAIL] \n");
      break;
    }

    if(f1->getResult<int>() != 333) {
      printf("---[Future PriorityPoolExecutor Cancel case5 -------[FAIL] \n");
      break;
    }
    pool->shutdown();
    pool->awaitTermination();
    break;
  }

  while(1) {
    auto pool = createExecutorBuilder()
                ->setThreadNum(1)
                ->newPriorityThreadPool();
    pool->submit(st(Executor)::High,[]{
      usleep(100*1000);
    });

    ArrayList<Future> lists = createArrayList<Future>();
    for(int i = 0;i < 1024;i++) {
      Future f = pool->submit(st(Executor)::High,[] {

      });
      lists->add(f);
    }

    pool->shutdown();
    pool->awaitTermination();

    auto iterator = lists->getIterator();
    while(iterator->hasValue()) {
      auto f = iterator->getValue();
      if(f->getStatus() != st(Future)::Cancel) {
        printf("---[Future PriorityPoolExecutor Cancel case6 -------[FAIL] \n");
        break;
      }
      iterator->next();
    }
    break;
  }

  while(1) {
    auto pool = createExecutorBuilder()
                ->setThreadNum(12)
                ->newPriorityThreadPool();
    pool->submit(st(Executor)::High,[]{
      usleep(100*1000);
    });

    ArrayList<Future> lists = createArrayList<Future>();
    for(int i = 0;i < 1024*32;i++) {
      Future f = pool->submit(st(Executor)::High,[] {
        usleep(1*1000);
      });
      lists->add(f);
    }

    Thread t = createThread([&lists] {
      auto iterator = lists->getIterator();
      while(iterator->hasValue()) {
        auto f = iterator->getValue();
        f->cancel();
        iterator->next();
      }
    });
    t->start();
    t->join();

    pool->shutdown();
    pool->awaitTermination();

    int count = 0;
    auto iterator = lists->getIterator();
    while(iterator->hasValue()) {
      auto f = iterator->getValue();
      if(f->getStatus() == st(Future)::Cancel) {
        count++;
      }
      iterator->next();
    }

    printf("---[Future PriorityPoolExecutor Cancel case7 -------[OK],count is %d \n",count);
    break;
  }

  printf("---[Future PriorityPoolExecutor Cancel case100 -------[OK] \n");
}