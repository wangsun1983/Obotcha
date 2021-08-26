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
#include "Error.hpp"

using namespace obotcha;

int runDestory = 1;
DECLARE_CLASS(BaseRunTest1) IMPLEMENTS(Runnable) {
public:
    void run() {
        printf("i am running \n");
        sleep(5);
        printf("i am wake \n");
    }

    ~_BaseRunTest1() {
        //printf("i am release \n");
        runDestory = 0;
    }
};

Mutex runTest2Mutex;
DECLARE_CLASS(BaseRunTest2) IMPLEMENTS(Runnable) {
public:
    void run() {
        //printf("RunTest2 start 1\n");
        //runTest2Mutex->lock();
        //printf("RunTest2 start 2\n");
    }
};


int baseTest() {
    //printf("---[TestScheduledThreadPoolExecutor Test Start]--- \n");

    //_ScheduledThreadPoolExecutor()
    while(1) {
        ThreadScheduledPoolExecutor pool = createExecutorBuilder()->newScheduledThreadPool();

        pool->shutdown();
        printf("---[ScheduledThreadPoolExecutor Test {constructor()} case1] [OK]--- \n");
        break;
    }


    //void shutdown();
    while(1) {
        ThreadScheduledPoolExecutor pool = createExecutorBuilder()->newScheduledThreadPool();
        printf("shudown trace1 \n");
        pool->submit(0,createBaseRunTest1());
        printf("shudown trace2 \n");
        pool->shutdown();
        printf("shudown trace3 \n");
        sleep(5);
        printf("shudown trace4 \n");
        //if(!pool->isShutdown()) {
        //    printf("---[ScheduledThreadPoolExecutor Test {shutdown()} case1] [FAIL]--- \n");
        //    break;
        //}

        Future task = pool->submit(0,createBaseRunTest1());
        printf("shudown trace5 \n");
        if(task != nullptr) {
            printf("---[ScheduledThreadPoolExecutor Test {shutdown()} case2] [FAIL]--- \n");
            break;
        }

        auto result = pool->submit(0,createBaseRunTest1());
        if(result != nullptr) {
            printf("---[ScheduledThreadPoolExecutor Test {shutdown()} case3] [FAIL]--- \n");
            break;
        }

        printf("---[ScheduledThreadPoolExecutor Test {shutdown()} case4] [OK]--- \n");
        break;
    }


    //int awaitTermination(long timeout);
    while(1) {
        ThreadScheduledPoolExecutor pool = createExecutorBuilder()->newScheduledThreadPool();
        int result = pool->awaitTermination(1000);
        if(result != -InvalidStatus) {
            printf("---[ScheduledThreadPoolExecutor Test {awaitTermination()} case1] [FAIL]--- \n");
            break;
        }

        //runTest2Mutex = createMutex();
        //runTest2Mutex->lock();

        pool->submit(0,createBaseRunTest2());
        sleep(1);
        pool->shutdown();

        long current = st(System)::currentTimeMillis();
        printf("awaitTermination start test \n");
        result = pool->awaitTermination(5000);
        printf("awaitTermination result is %d \n",result);
        if(result != 0) {
            printf("---[ScheduledThreadPoolExecutor Test {awaitTermination()} case2] [FAIL]--- \n");
            break;
        }
        long current2 = st(System)::currentTimeMillis();
        printf("current2 - current1 is %d \n",(current2 - current));
        if(current2 - current > 15) {
            printf("---[ScheduledThreadPoolExecutor Test {awaitTermination()} case3] [FAIL]--- \n");
            break;
        }

        printf("---[ScheduledThreadPoolExecutor Test {awaitTermination()} case4] [OK]--- \n");
        break;
    }


    //int awaitTermination(long timeout = 0);
    while(1) {
        ThreadScheduledPoolExecutor pool = createExecutorBuilder()->newScheduledThreadPool();
        int result = pool->awaitTermination(0);
        if(result != -InvalidStatus) {
            printf("---[ScheduledThreadPoolExecutor Test {awaitTermination()} case5] [FAIL]--- \n");
            break;
        }

        pool->submit(0,createBaseRunTest1());
        int v = pool->shutdown();
        printf("v is %d \n",v);

        long current = st(System)::currentTimeMillis();
        printf("awaitTermination start test \n");
        result = pool->awaitTermination(0);
        printf("awaitTermination result is %d \n",result);
        if(result != 0) {
            printf("---[ScheduledThreadPoolExecutor Test {awaitTermination()} case6] [FAIL]--- \n");
            break;
        }

        long current2 = st(System)::currentTimeMillis();
        //printf("current2 - current1 is %d \n",(current2 - current));
        if(current2 - current > 10005) {
            printf("---[ScheduledThreadPoolExecutor Test {awaitTermination()} case7] [FAIL]--- \n");
            break;
        }

        printf("---[ScheduledThreadPoolExecutor Test {awaitTermination()} case8] [OK]--- \n");
        break;
    }



    //int awaitTermination(long timeout = max);
    while(1) {
        ThreadScheduledPoolExecutor pool = createExecutorBuilder()->newScheduledThreadPool();
        pool->submit(0,createBaseRunTest1());
        pool->shutdown();

        long current = st(System)::currentTimeMillis();
        pool->awaitTermination(100000);
        int v = st(System)::currentTimeMillis() - current;
        printf("v is %d \n",v);
        if(v > 10005) {
            printf("---[ScheduledThreadPoolExecutor Test {awaitTermination()} case9] [FAIL]--- \n");
            break;
        }

        printf("---[ScheduledThreadPoolExecutor Test {awaitTermination()} case10] [OK]--- \n");
        break;
    }



    //submit(Runnable task);
    while(1) {
        ThreadScheduledPoolExecutor pool = createExecutorBuilder()->newScheduledThreadPool();
        Future task = pool->submit(0,createBaseRunTest1());
        if(task == nullptr) {
            printf("---[ScheduledThreadPoolExecutor Test {submit()} case1] [FAIL]--- \n");
            break;
        }

        //long current = st(System)::currentTimeMillis();
        //Future task2 = pool->submit(createRunTest1());
        //int v = st(System)::currentTimeMillis() - current;
        //if(v >10005) {
        //    printf("---[ScheduledThreadPoolExecutor Test {submit()} case2] [FAIL]--- \n");
        //    break;
        //}
        pool->shutdown();
        printf("---[ScheduledThreadPoolExecutor Test {submit()} case3] [OK]--- \n");
        break;
    }
}
