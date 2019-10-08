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
#include "PriorityPoolExecutor.hpp"

using namespace obotcha;

int runDestory = 1;
DECLARE_SIMPLE_CLASS(RunTest1) IMPLEMENTS(Runnable) {
public:
    void run() {
        //printf("i am running 1\n");
        sleep(10);
        //printf("i am running 2\n");
        
    }

    void onInterrupt() {
        //printf("i am interrupt1111 \n");
        runDestory = 2;
    }

    ~_RunTest1() {
        //printf("i am release2222 \n");
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
};


int priorityPoolNormalTest() {
    printf("---[TestPriorityPoolExecutor Test Start]--- \n");

    //_ThreadPoolExecutor(int queuesize,int threadnum);
    while(1) {
        ExecutorService pool = st(Executors)::newPriorityThreadPool();
        printf("---[TestPriorityPoolExecutor Test {constructor()} case1] [Success]--- \n");
        break;
    }

    //_ThreadPoolExecutor();
    while(1) {
        ExecutorService pool = st(Executors)::newPriorityThreadPool();
        printf("---[TestPriorityPoolExecutor Test {constructor2()} case1] [Success]--- \n");
        break;
    }

    //void shutdown();
    while(1) {
        ExecutorService pool = st(Executors)::newPriorityThreadPool();
        pool->submit(createRunTest1());
        pool->shutdown();
        sleep(5);
        if(!pool->isShutdown()) {
            printf("---[TestPriorityPoolExecutor Test {shutdown()} case1] [FAIL]--- \n");
            break;
        }

        Future task = pool->submit(createRunTest1());
        if(task != nullptr) {
            printf("---[TestPriorityPoolExecutor Test {shutdown()} case2] [FAIL]--- \n");
            break;
        }

        int result = pool->execute(createRunTest1());
        if(result != -InvalidStatus) {
            printf("---[TestPriorityPoolExecutor Test {shutdown()} case3] [FAIL]--- \n");
            break;
        }

        printf("---[TestPriorityPoolExecutor Test {shutdown()} case4] [Success]--- \n");
        break;
    }


    //int awaitTermination(long timeout);
    while(1) {
        ExecutorService pool = st(Executors)::newPriorityThreadPool();
        int result = pool->awaitTermination(1000);
        if(result != -InvalidStatus) {
            printf("---[TestPriorityPoolExecutor Test {awaitTermination()} case1] [FAIL]--- \n");
            break;
        }

        runTest2Mutex = createMutex();
        runTest2Mutex->lock();

        pool->submit(createRunTest2());
        sleep(1);
        pool->shutdown();

        long current = st(System)::currentTimeMillis();
        result = pool->awaitTermination(5000);
        if(result != -WaitTimeout) {
            printf("---[TestPriorityPoolExecutor Test {awaitTermination()} case2] [FAIL]--- \n");
            break;
        }
        long current2 = st(System)::currentTimeMillis();
        //printf("current2 - current1 is %d \n",(current2 - current));
        if(current2 - current > 5005) {
            printf("---[TestPriorityPoolExecutor Test {awaitTermination()} case3] [FAIL]--- \n");
            break;
        }

        printf("---[TestPriorityPoolExecutor Test {awaitTermination()} case4] [Success]--- \n");
        break;
    }

    //int awaitTermination(long timeout = max);
    while(1) {
        ExecutorService pool = st(Executors)::newPriorityThreadPool();
        pool->submit(createRunTest1());
        pool->shutdown();

        long current = st(System)::currentTimeMillis();
        pool->awaitTermination(100000);
        int v = st(System)::currentTimeMillis() - current;
        if(v > 10005) {
            printf("---[TestPriorityPoolExecutor Test {awaitTermination()} case9] [FAIL]--- \n");
            break;
        }

        printf("---[TestPriorityPoolExecutor Test {awaitTermination()} case10] [Success]--- \n");
        break;
    }


    //submit(Runnable task);
    while(1) {
        ExecutorService pool = st(Executors)::newPriorityThreadPool();
        Future task = pool->submit(createRunTest1());
        if(task == nullptr) {
            printf("---[TestPriorityPoolExecutor Test {submit()} case1] [FAIL]--- \n");
            break;
        }

        long current = st(System)::currentTimeMillis();
        Future task2 = pool->submit(createRunTest1());
        int v = st(System)::currentTimeMillis() - current;
        if(v >10005) {
            printf("---[TestPriorityPoolExecutor Test {submit()} case2] [FAIL]--- \n");
            break;
        }

        printf("---[TestPriorityPoolExecutor Test {submit()} case3] [Success]--- \n");
        break;
    }
   
}

