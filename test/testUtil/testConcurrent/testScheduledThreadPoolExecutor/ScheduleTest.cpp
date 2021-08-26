#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ThreadScheduledPoolExecutor.hpp"
#include "Integer.hpp"
#include "ExecutorBuilder.hpp"
#include "Future.hpp"
#include "System.hpp"

using namespace obotcha;

long RunTestTime1 = 1;
long RunTestTime2 = 1;

DECLARE_CLASS(ScheduleRunTest1) IMPLEMENTS(Runnable) {
public:
    void run() {
        RunTestTime1 = st(System)::currentTimeMillis();
        printf("RunTest1 start,RunTestTime1 is %ld \n",RunTestTime1);
        //printf("================= thread post %ld \n",st(System)::currentTimeMillis());
        sleep(5);
    }

    ~_ScheduleRunTest1() {
        //printf("i am release .......aaaa,p is %x\n",this);
    }
};

DECLARE_CLASS(ScheduleRunTest2) IMPLEMENTS(Runnable) {
public:
    void run() {
        RunTestTime2 = st(System)::currentTimeMillis();
        printf("RunTest2 start,RunTestTime2 is %ld \n",RunTestTime2);
        sleep(5);
    }
};

int runTest3Val = 0;
DECLARE_CLASS(RunTest3) IMPLEMENTS(Runnable) {
public:
    void run() {
        runTest3Val = 1;
    }
};


int scheduleTest() {
    //printf("---[TestScheduledThreadPoolExecutor Test Start]--- \n");
    //schedule test
    while(1) {
        ThreadScheduledPoolExecutor pool = createExecutorBuilder()->newScheduledThreadPool();
        long current = st(System)::currentTimeMillis();
        printf("================= start post %ld \n",st(System)::currentTimeMillis());
        pool->submit(5000,createScheduleRunTest1());
        pool->submit(5000,createScheduleRunTest2());
        sleep(15);
        printf("RunTestTime1 is %ld \n",RunTestTime1);
        printf("RunTestTime2 is %ld \n",RunTestTime2);
        long v = (RunTestTime1 - RunTestTime2);
        if(v > 50 || v < -50) {
            pool->shutdown();
            printf("---[ScheduledThreadPoolExecutor Test {schedule()} case1,v is %ld] [FAIL]--- \n",v);
            break;
        }
        printf("run test time1 is %ld \n",RunTestTime1);
        printf("run test time2 is %ld \n",RunTestTime2);
        printf("run test current is %ld \n",current);


        int inter = (RunTestTime1 - current - 5000);
        if(inter > 10) {
            pool->shutdown();
            printf("---[ScheduledThreadPoolExecutor Test {schedule(),inter is %d} case2] [FAIL]--- \n",inter);
            break;
        }
        pool->shutdown();
        printf("---[ScheduledThreadPoolExecutor Test {schedule()} case3] [OK]--- \n");
        break;
    }

#if 0
    //schedule
    while(1) {
        ThreadScheduledPoolExecutor pool = createExecutorBuilder()->newScheduledThreadPool();
        Future f = pool->submit(createRunTest1(),5000);
        sleep(1);
        f->cancel();
        sleep(5);
        if(runTest3Val == 1) {
            printf("---[ScheduledThreadPoolExecutor Test {schedule,cancel()} case1] [FAIL]--- \n");
            break;
        }

        printf("---[ScheduledThreadPoolExecutor Test {schedule,cancel()} case2] [OK]--- \n");
        break;
    }

    //schedule
    while(1) {
        runTest3Val = 0;

        ThreadScheduledPoolExecutor pool = createExecutorBuilder()->newScheduledThreadPool();
        Future f = pool->submit(createRunTest1(),5000);
        sleep(1);
        printf("f trace1 \n");
        pool->shutdown();
        printf("f trace2 \n");
        sleep(8);
        if(runTest3Val == 1) {
            printf("---[ScheduledThreadPoolExecutor Test {schedule,shutdown()} case1] [FAIL]--- \n");
            break;
        }

        printf("---[ScheduledThreadPoolExecutor Test {schedule,shutdown()} case2] [OK]--- \n");
        break;
    }
#endif
}
