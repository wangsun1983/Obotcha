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
#include "AutoClose.hpp"

using namespace obotcha;

int runDestory = 1;
DECLARE_SIMPLE_CLASS(RunTest1) IMPLEMENTS(Runnable) {
public:
    void run() {
        printf("i am running \n");
        sleep(10);
        printf("i am running end\n");
    }

    void onInterrupt() {
        printf("i am interrupt \n");
    }

    ~_RunTest1() {
        printf("i am release \n");
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


int normalTest() {
    printf("---[TestCachedPoolExecutor Test Start]--- \n");
    //_ThreadCachedPoolExecutor(int queuesize,int minthreadnum,int maxthreadnum,long timeout);

    while(1) {
        ExecutorService pool = st(Executors)::newCachedThreadPool(1,1,2,60*1000);
        
        pool->shutdown();
        printf("---[TestCachedPoolExecutor Test {constructor()} case1] [Success]--- \n");
        break;
    }


    //_ThreadCachedPoolExecutor(int maxthreadnum,long timeout);
    while(1) {
        ExecutorService pool = st(Executors)::newCachedThreadPool(2,60*1000);
        
        printf("---[TestCachedPoolExecutor Test {constructor2()} case2] [Success]--- \n");
        pool->shutdown();
        break;
    }

    //_ThreadCachedPoolExecutor();
    while(1) {
        ExecutorService pool = st(Executors)::newCachedThreadPool();
        pool->shutdown();
        printf("---[TestCachedPoolExecutor Test {constructor2()} case3] [Success]--- \n");
        break;
    }  


    //void shutdown();
    while(1) {
        ExecutorService pool = st(Executors)::newCachedThreadPool();
        printf("submit count1 is %d \n",pool->getStrongCount());
        pool->submit(createRunTest1());
        printf("submit count2 is %d \n",pool->getStrongCount());
        sleep(1);
        printf("shutdown start1\n");
        pool->shutdown();
        printf("shutdown start2\n");
        sleep(5);
        if(!pool->isShutdown()) {
            printf("---[TestCachedPoolExecutor Test {shutdown()} case1] [FAIL]--- \n");
            break;
        }

        Future task = pool->submit(createRunTest1());
        if(task != nullptr) {
            printf("---[TestCachedPoolExecutor Test {shutdown()} case2] [FAIL]--- \n");
            break;
        }

        int result = pool->execute(createRunTest1());
        if(result != -InvalidStatus) {
            printf("---[TestCachedPoolExecutor Test {shutdown()} case3] [FAIL]--- \n");
            break;
        }

        printf("---[TestCachedPoolExecutor Test {shutdown()} case4] [Success],count is %d --- \n",pool->getStrongCount());
        break;

    }

    //int awaitTermination(long timeout);
    while(1) {
        ExecutorService pool = st(Executors)::newCachedThreadPool();
        
        int result = pool->awaitTermination(1000);
        if(result != -InvalidStatus) {
            printf("---[TestCachedPoolExecutor Test {awaitTermination()} case1] [FAIL]--- \n");
            break;
        }

        runTest2Mutex = createMutex();
        runTest2Mutex->lock();

        pool->submit(createRunTest2());
        sleep(1);
        pool->shutdown();

        long current = st(System)::currentTimeMillis();
        printf("awaitTermination start test \n");
        result = pool->awaitTermination(5000);
        printf("awaitTermination result is %d \n",result);
        if(result != -WaitTimeout) {
            printf("---[TestCachedPoolExecutor Test {awaitTermination()} case2] [FAIL]--- \n");
            runTest2Mutex->unlock();
            pool->shutdown();
            break;
        }
        long current2 = st(System)::currentTimeMillis();
        printf("current2 - current1 is %d \n",(current2 - current));
        if(current2 - current > 5010) {
            printf("---[TestCachedPoolExecutor Test {awaitTermination()} case3] [FAIL]--- \n");
            runTest2Mutex->unlock();
            pool->shutdown();
            break;
        }

        pool->shutdown();
        printf("---[TestCachedPoolExecutor Test {awaitTermination()} case4] [Success]--- \n");
        runTest2Mutex->unlock();
        break;
    }

    //int awaitTermination(long timeout = 0);
    while(1) {
        ExecutorService pool = st(Executors)::newCachedThreadPool();
        
        int result = pool->awaitTermination(0);
        if(result != -InvalidStatus) {
            printf("---[TestCachedPoolExecutor Test {awaitTermination()} case5] [FAIL]--- \n");
            pool->shutdown();
            break;
        }

        pool->submit(createRunTest1());
        pool->shutdown();

        long current = st(System)::currentTimeMillis();
        printf("awaitTermination start test \n");
        result = pool->awaitTermination(0);
        printf("awaitTermination result is %d \n",result);
        if(result != 0) {
            printf("---[TestCachedPoolExecutor Test {awaitTermination()} case6] [FAIL]--- \n");
            pool->shutdown();
            break;
        }

        long current2 = st(System)::currentTimeMillis();
        //printf("current2 - current1 is %d \n",(current2 - current));
        if(current2 - current > 10005) {
            printf("---[TestCachedPoolExecutor Test {awaitTermination()} case7,interval is %ld] [FAIL]--- \n",current2 - current);
            break;
        }

        printf("---[TestCachedPoolExecutor Test {awaitTermination()} case8] [Success]--- \n");
        break;
    }

    //int awaitTermination(long timeout = max);
    while(1) {
        ExecutorService pool = st(Executors)::newCachedThreadPool();
        
        pool->submit(createRunTest1());
        pool->shutdown();

        long current = st(System)::currentTimeMillis();
        pool->awaitTermination(100000);
        int v = st(System)::currentTimeMillis() - current;
        if(v > 10005) {
            printf("---[TestCachedPoolExecutor Test {awaitTermination()} case9] [FAIL]--- \n");
            break;
        }

        printf("---[TestCachedPoolExecutor Test {awaitTermination()} case10] [Success]--- \n");
        break;
    }

    //int getThreadsNum();
    while(1) {
        ExecutorService pool = st(Executors)::newCachedThreadPool();
        
        printf("thread num is %d \n",pool->getThreadsNum());
        if(pool->getThreadsNum() != 0) {
            printf("---[TestCachedPoolExecutor Test {getThreadsNum()} case1] [FAIL]--- \n");
            break;
        }
        pool->shutdown();
        printf("---[TestCachedPoolExecutor Test {getThreadsNum()} case2] [Success]--- \n");
        break;
    }
   
 
    //submit(Runnable task);
    while(1) {
        ExecutorService pool = st(Executors)::newCachedThreadPool();
        
        Future task = pool->submit(createRunTest1());
        if(task == nullptr) {
            printf("---[TestCachedPoolExecutor Test {submit()} case1] [FAIL]--- \n");
            break;
        }

        long current = st(System)::currentTimeMillis();
        Future task2 = pool->submit(createRunTest1());
        int v = st(System)::currentTimeMillis() - current;
        if(v >10005) {
            printf("---[TestCachedPoolExecutor Test {submit()} case2] [FAIL]--- \n");
            break;
        }

        pool->shutdown();
        printf("---[TestCachedPoolExecutor Test {submit()} case3] [Success]--- \n");
        break;
    }
     

    //submit(Runnable task);
    while(1) {
        ExecutorService pool = st(Executors)::newCachedThreadPool();
        
        Future task = pool->submit(createRunTest1());
        sleep(1);
        if(pool->getThreadsNum() != 1) {
            printf("---[TestCachedPoolExecutor Test {submit()} case4] [FAIL]--- \n");
            break;
        }

        sleep(100);
        if(pool->getThreadsNum() != 0) {
            printf("---[TestCachedPoolExecutor Test {submit()} case5] [FAIL]--- \n");
            break;
        }

        pool->shutdown();
        printf("---[TestCachedPoolExecutor Test {submit()} case6] [Success]--- \n");
        break;
    }

}

