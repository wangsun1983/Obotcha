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
#include "ThreadPoolExecutor.hpp"

using namespace obotcha;


int runDestory = 1;
DECLARE_SIMPLE_CLASS(MyRunTest1) IMPLEMENTS(Runnable) {
public:
    void run() {
        //printf("i am running123 \n");
        sleep(10);
    }

    void onInterrupt() {
        //printf("i am interrupt \n");
        runDestory = 2;
    }

    ~_MyRunTest1() {
        //printf("i am release \n");
        runDestory = 0;
    }
};

Mutex runTest2Mutex;
DECLARE_SIMPLE_CLASS(RunTest2) IMPLEMENTS(Runnable) {
public:
    void run() {
        //printf("RunTest2 start 1\n");
        runTest2Mutex->lock();
        //printf("RunTest2 start 2\n");
    }

    void onInterrupt() {
        //printf("RunTest2 onInterrupt 2\n");
    }

    ~_RunTest2() {
        //printf("RunTest2 dispose 2\n");
    }
};


int normalTest() {
    printf("---[PriorityPoolExecutor Normal Test Start]--- \n");
    //_ThreadPoolExecutor(int queuesize,int threadnum);
   
    while(1) {
        {
            ExecutorService pool = st(Executors)::newPriorityThreadPool();
            pool->shutdown();
        }

        sleep(1);        

        printf("---[PriorityPoolExecutor Test {constructor()} case1] [Success]--- \n");
        break;
    }
    
    //_ThreadPoolExecutor();
    while(1) {
        ExecutorService pool = st(Executors)::newPriorityThreadPool();
        pool->shutdown();
        printf("---[PriorityPoolExecutor Test {constructor2()} case1] [Success]--- \n");
        break;
    }


    //void shutdown();
    while(1) {
        ExecutorService pool = st(Executors)::newPriorityThreadPool();
        pool->submit(createMyRunTest1());
        pool->shutdown();
        sleep(5);
        if(!pool->isShutdown()) {
            printf("---[PriorityPoolExecutor Test {shutdown()} case1] [FAIL]--- \n");
            break;
        }

        Future task = pool->submit(createMyRunTest1());
        if(task != nullptr) {
            printf("---[PriorityPoolExecutor Test {shutdown()} case2] [FAIL]--- \n");
            break;
        }

        int result = pool->execute(createMyRunTest1());
        if(result != -AlreadyDestroy) {
            printf("---[PriorityPoolExecutor Test {shutdown()} case3] [FAIL]--- \n");
            break;
        }

        printf("---[PriorityPoolExecutor Test {shutdown()} case4] [Success]--- \n");
        break;
    }

    //int awaitTermination(long timeout);
    while(1) {
        ExecutorService pool = st(Executors)::newPriorityThreadPool();
        int result = pool->awaitTermination(1000);
        if(result != -InvalidStatus) {
            printf("---[PriorityPoolExecutor Test {awaitTermination()} case1] [FAIL]--- \n");
            break;
        }

        runTest2Mutex = createMutex();
        runTest2Mutex->lock();

        pool->submit(createRunTest2());
        sleep(1);
        pool->shutdown();

        long current = st(System)::currentTimeMillis();
        //printf("awaitTermination start test \n");
        result = pool->awaitTermination(5000);
        //printf("awaitTermination result is %d \n",result);
        if(result != -WaitTimeout) {
            printf("---[PriorityPoolExecutor Test {awaitTermination()} case2] [FAIL]--- \n");
            break;
        }

        long current2 = st(System)::currentTimeMillis();
        printf("current2 - current1 is %d \n",(current2 - current));
        if(current2 - current > 5015) {
            printf("---[PriorityPoolExecutor Test {awaitTermination()} case3] [FAIL]--- \n");
            break;
        }

        printf("---[PriorityPoolExecutor Test {awaitTermination()} case4] [Success]--- \n");
        runTest2Mutex->unlock();
        break;
    }
   

    //int awaitTermination(long timeout = 0);
    while(1) {
        ExecutorService pool = st(Executors)::newPriorityThreadPool();
        int result = pool->awaitTermination(0);
        if(result != -InvalidStatus) {
            printf("---[PriorityPoolExecutor Test {awaitTermination()} case5] [FAIL]--- \n");
            break;
        }

        pool->submit(createMyRunTest1());
        pool->shutdown();

        long current = st(System)::currentTimeMillis();
        //printf("awaitTermination start test \n");
        result = pool->awaitTermination(0);
        //printf("awaitTermination result is %d \n",result);
        if(result != 0) {
            printf("---[PriorityPoolExecutor Test {awaitTermination()} case6] [FAIL]--- \n");
            break;
        }

        long current2 = st(System)::currentTimeMillis();
        //printf("current2 - current1 is %d \n",(current2 - current));
        if(current2 - current > 10005) {
            printf("---[PriorityPoolExecutor Test {awaitTermination()} case7] [FAIL]--- \n");
            break;
        }

        printf("---[PriorityPoolExecutor Test {awaitTermination()} case8] [Success]--- \n");
        break;
    }

  
    //int awaitTermination(long timeout = max);
    while(1) {
        ExecutorService pool = st(Executors)::newPriorityThreadPool();
        pool->submit(createMyRunTest1());
        pool->shutdown();

        long current = st(System)::currentTimeMillis();
        pool->awaitTermination(100000);
        int v = st(System)::currentTimeMillis() - current;
        if(v > 10005) {
            printf("---[PriorityPoolExecutor Test {awaitTermination()} case9] [FAIL]--- \n");
            break;
        }

        printf("---[PriorityPoolExecutor Test {awaitTermination()} case10] [Success]--- \n");
        break;
    }
   

    //int getThreadsNum();
    while(1) {
        ExecutorService pool = st(Executors)::newPriorityThreadPool();
        if(pool->getThreadsNum() != 100) {
            printf("---[PriorityPoolExecutor Test {getThreadsNum()} case1] [FAIL]--- \n");
            break;
        }
        pool->shutdown();
        printf("---[PriorityPoolExecutor Test {getThreadsNum()} case2] [Success]--- \n");
        break;
    }

    //submit(Runnable task);
    while(1) {
        ExecutorService pool = st(Executors)::newPriorityThreadPool();
        Future task = pool->submit(createMyRunTest1());
        if(task == nullptr) {
            printf("---[PriorityPoolExecutor Test {submit()} case1] [FAIL]--- \n");
            break;
        }

        long current = st(System)::currentTimeMillis();
        Future task2 = pool->submit(createMyRunTest1());
        int v = st(System)::currentTimeMillis() - current;
        if(v >10005) {
            printf("---[PriorityPoolExecutor Test {submit()} case2] [FAIL]--- \n");
            break;
        }
        pool->shutdown();
        printf("---[PriorityPoolExecutor Test {submit()} case3] [Success]--- \n");
        break;
    }
   
}

