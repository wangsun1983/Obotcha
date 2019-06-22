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

using namespace obotcha;

long RunTestTime1 = 1;
long RunTestTime2 = 1;

DECLARE_SIMPLE_CLASS(RunTest1) IMPLEMENTS(Runnable) {
public:
    void run() {
        RunTestTime1 = st(System)::currentTimeMillis();
        printf("RunTest1 start,RunTestTime1 is %ld \n",RunTestTime1);
        sleep(5);
    }
};

DECLARE_SIMPLE_CLASS(RunTest2) IMPLEMENTS(Runnable) {
public:
    void run() {
        RunTestTime2 = st(System)::currentTimeMillis();
        printf("RunTest2 start,RunTestTime2 is %ld \n",RunTestTime2);   
        sleep(5);
    }
};

int runTest3Val = 0;
DECLARE_SIMPLE_CLASS(RunTest3) IMPLEMENTS(Runnable) {
public:
    void run() {
        runTest3Val = 1;
    }
};


int scheduleTest() {
    //printf("---[TestScheduledThreadPoolExecutor Test Start]--- \n");
    //schedule test
    while(1) {
        ScheduledExecutorService pool = st(Executors)::newScheduledThreadPool();
        long current = st(System)::currentTimeMillis();
        pool->schedule(createRunTest1(),5000);
        pool->schedule(createRunTest2(),5000);
        sleep(15);
        printf("RunTestTime1 is %ld ",RunTestTime1);
        printf("RunTestTime2 is %ld ",RunTestTime2);
        long v = (RunTestTime1 - RunTestTime2);
        printf("v is %ld \n",v);
        if(v > 10 || v < -10) {
            printf("---[ScheduledThreadPoolExecutor Test {schedule()} case1,v is %ld] [FAIL]--- \n",v);
            break;
        }
        int inter = RunTestTime1 - current - 5000;
        if(inter > 10) {
            printf("---[ScheduledThreadPoolExecutor Test {schedule(),inter is %d} case2] [FAIL]--- \n",inter);
            break;
        }

        printf("---[ScheduledThreadPoolExecutor Test {schedule()} case3] [Success]--- \n");
        break;
    }

    //schedule
    while(1) {
        ScheduledExecutorService pool = st(Executors)::newScheduledThreadPool();
        Future f = pool->schedule(createRunTest1(),5000);
        sleep(1);
        f->cancel();
        sleep(5);
        if(runTest3Val == 1) {
            printf("---[ScheduledThreadPoolExecutor Test {schedule,cancel()} case1] [FAIL]--- \n");
            break;
        }

        printf("---[ScheduledThreadPoolExecutor Test {schedule,cancel()} case2] [Success]--- \n");
        break;
    }

    //schedule
    while(1) {
        runTest3Val = 0;

        ScheduledExecutorService pool = st(Executors)::newScheduledThreadPool();
        Future f = pool->schedule(createRunTest1(),5000);
        sleep(1);
        pool->shutdown();
        sleep(8);
        if(runTest3Val == 1) {
            printf("---[ScheduledThreadPoolExecutor Test {schedule,shutdown()} case1] [FAIL]--- \n");
            break;
        }

        printf("---[ScheduledThreadPoolExecutor Test {schedule,shutdown()} case2] [Success]--- \n");
        break;
    }

    //schedule
    while(1) {
        runTest3Val = 0;
        ScheduledExecutorService pool = st(Executors)::newScheduledThreadPool();
        Future f = pool->schedule(createRunTest1(),5000);
        sleep(1);
        pool->shutdownNow();
        sleep(8);
        if(runTest3Val == 1) {
            printf("---[ScheduledThreadPoolExecutor Test {schedule,shutdownNow()} case1] [FAIL]--- \n");
            break;
        }

        printf("---[ScheduledThreadPoolExecutor Test {schedule,shutdownNow()} case2] [Success]--- \n");
        break;
    }

}

