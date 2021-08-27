#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ThreadPriorityPoolExecutor.hpp"
#include "Integer.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "ExecutorBuilder.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

void testSubmitPriority() {
  TimeWatcher watch = createTimeWatcher();
  while(1) {
    auto pool = createExecutorBuilder()
              ->setQueueSize(32)
              ->setThreadNum(1)
              ->newPriorityThreadPool();

    pool->submit(st(Executor)::Medium,[]{
      usleep(100*1000);
    });
    usleep(10*1000);

    long task1time;
    long task2time;
    long task3time;
    pool->submit(st(Executor)::Medium,[&task1time]{
      task1time = st(System)::currentTimeMillis();
      usleep(10*1000);
    });

    pool->submit(st(Executor)::High,[&task2time]{
      task2time = st(System)::currentTimeMillis();
      usleep(10*1000);
    });

    pool->submit(st(Executor)::High,[&task3time]{
      task3time = st(System)::currentTimeMillis();
      usleep(10*1000);
    });

    usleep(200*1000);
    if(task2time > task1time || (task1time - task2time) > 25 || (task1time - task2time) < 20) {
      printf("---[TestPriorityPoolExecutor SubmitPriority Test case1] [FAILED]--- interval %ld\n",task1time - task2time);
      break;
    }

    if(task2time > task3time || (task3time - task2time) > 15) {
      printf("---[TestPriorityPoolExecutor SubmitPriority Test case2] [FAILED]--- interval is %ld\n",task3time - task2time);
      break;
    }

    pool->shutdown();
    pool->awaitTermination();
    break;
  }

  while(1) {
    auto pool = createExecutorBuilder()
              ->setQueueSize(32)
              ->setThreadNum(1)
              ->newPriorityThreadPool();

    pool->submit(st(Executor)::Medium,[]{
      usleep(100*1000);
    });
    usleep(10*1000);

    long task1time;
    long task2time;
    long task3time;

    pool->submit(st(Executor)::Low,[&task1time]{
      task1time = st(System)::currentTimeMillis();
      usleep(10*1000);
    });

    pool->submit(st(Executor)::Medium,[&task2time]{
      task2time = st(System)::currentTimeMillis();
      usleep(10*1000);
    });

    pool->submit(st(Executor)::High,[&task3time]{
      task3time = st(System)::currentTimeMillis();
      usleep(10*1000);
    });

    usleep(200*1000);
    if(task2time > task1time || (task1time - task2time) > 15 || (task1time - task2time) < 10) {
      printf("---[TestPriorityPoolExecutor SubmitPriority Test case2] [FAILED]--- interval %ld\n",task1time - task2time);
      break;
    }

    if(task3time > task2time || (task2time - task3time) > 15 || (task2time - task3time) < 10) {
      printf("---[TestPriorityPoolExecutor SubmitPriority Test case3] [FAILED]--- interval %ld\n",task2time - task3time);
      break;
    }

    pool->shutdown();
    pool->awaitTermination();
    break;
  }

  printf("---[TestPriorityPoolExecutor SubmitPriority Test case100] [OK]--- \n");

}
