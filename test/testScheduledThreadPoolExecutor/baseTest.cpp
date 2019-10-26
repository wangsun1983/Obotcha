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
#include "Error.hpp"

using namespace obotcha;

int runDestory = 1;
DECLARE_SIMPLE_CLASS(BaseRunTest1) IMPLEMENTS(Runnable) {
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
DECLARE_SIMPLE_CLASS(BaseRunTest2) IMPLEMENTS(Runnable) {
public:
    void run() {
        //printf("RunTest2 start 1\n");
        //runTest2Mutex->lock();
        //printf("RunTest2 start 2\n");
    }
};


int baseTest() {
    //printf("---[TestScheduledThreadPoolExecutor Test Start]--- \n");
#if 0
    //_ScheduledThreadPoolExecutor()
    while(1) {
        ExecutorService pool = st(Executors)::newScheduledThreadPool();
        printf("---[ScheduledThreadPoolExecutor Test {constructor()} case1] [Success]--- \n");
        break;
    }


    //void shutdown();
    while(1) {
        ExecutorService pool = st(Executors)::newScheduledThreadPool();
        pool->submit(createRunTest1());
        pool->shutdown();
        sleep(5);
        if(!pool->isShutdown()) {
            printf("---[ScheduledThreadPoolExecutor Test {shutdown()} case1] [FAIL]--- \n");
            break;
        }

        Future task = pool->submit(createRunTest1());
        if(task != nullptr) {
            printf("---[ScheduledThreadPoolExecutor Test {shutdown()} case2] [FAIL]--- \n");
            break;
        }

        int result = pool->execute(createRunTest1());
        if(result != -InvalidStatus) {
            printf("---[ScheduledThreadPoolExecutor Test {shutdown()} case3] [FAIL]--- \n");
            break;
        }

        printf("---[ScheduledThreadPoolExecutor Test {shutdown()} case4] [Success]--- \n");
        break;
    }


    //int awaitTermination(long timeout);
    while(1) {
        ExecutorService pool = st(Executors)::newScheduledThreadPool();
        int result = pool->awaitTermination(1000);
        if(result != -InvalidStatus) {
            printf("---[ScheduledThreadPoolExecutor Test {awaitTermination()} case1] [FAIL]--- \n");
            break;
        }

        //runTest2Mutex = createMutex();
        //runTest2Mutex->lock();

        pool->submit(createRunTest2());
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
        //printf("current2 - current1 is %d \n",(current2 - current));
        if(current2 - current > 5) {
            printf("---[ScheduledThreadPoolExecutor Test {awaitTermination()} case3] [FAIL]--- \n");
            break;
        }

        printf("---[ScheduledThreadPoolExecutor Test {awaitTermination()} case4] [Success]--- \n");
        break;
    }


    //int awaitTermination(long timeout = 0);
    while(1) {
        ExecutorService pool = st(Executors)::newScheduledThreadPool();
        int result = pool->awaitTermination(0);
        if(result != -InvalidStatus) {
            printf("---[ScheduledThreadPoolExecutor Test {awaitTermination()} case5] [FAIL]--- \n");
            break;
        }

        pool->submit(createRunTest1());
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

        printf("---[ScheduledThreadPoolExecutor Test {awaitTermination()} case8] [Success]--- \n");
        break;
    }


    //int awaitTermination(long timeout = max);
    while(1) {
        ExecutorService pool = st(Executors)::newScheduledThreadPool();
        pool->submit(createRunTest1());
        pool->shutdown();

        long current = st(System)::currentTimeMillis();
        pool->awaitTermination(100000);
        int v = st(System)::currentTimeMillis() - current;
        if(v > 10005) {
            printf("---[ScheduledThreadPoolExecutor Test {awaitTermination()} case9] [FAIL]--- \n");
            break;
        }

        printf("---[ScheduledThreadPoolExecutor Test {awaitTermination()} case10] [Success]--- \n");
        break;
    }
#endif  

    //submit(Runnable task);
    while(1) {
        ExecutorService pool = st(Executors)::newScheduledThreadPool();
        Future task = pool->submit(createBaseRunTest1());
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
        printf("---[ScheduledThreadPoolExecutor Test {submit()} case3] [Success]--- \n");
        break;
    }
   
}

