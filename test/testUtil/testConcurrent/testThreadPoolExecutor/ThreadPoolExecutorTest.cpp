#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ThreadPoolExecutor.hpp"
#include "Integer.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "ExecutorBuilder.hpp"

using namespace obotcha;


int runDestory = 1;
DECLARE_CLASS(MyRunTest1) IMPLEMENTS(Runnable) {
public:
    void run() {
        printf("i am running123 1 \n");
        sleep(10);
        printf("i am running123 2\n");
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
DECLARE_CLASS(RunTest2) IMPLEMENTS(Runnable) {
public:
    void run() {
        fflush(stdout);
        printf("test2 trace \n");
        runTest2Mutex->lock();
        printf("test3 trace \n");
    }

    void onInterrupt() {
        //printf("RunTest2 onInterrupt 2\n");
    }

    ~_RunTest2() {
        //printf("RunTest2 dispose 2\n");
    }
};


void normalTest() {
    printf("---[TestThreadPoolExecutor Normal Test Start]--- \n");
    //_ThreadPoolExecutor(int queuesize,int threadnum);

    while(1) {
        {
			ThreadPoolExecutor pool = createExecutorBuilder()->setQueueSize(1)->setThreadNum(1)->newThreadPool();//st(Executors)::newFixedThreadPool(1,1);
			pool->shutdown();
		}

        sleep(1);

        printf("---[TestThreadPoolExecutor Test {constructor()} case1] [OK]--- \n");
        break;
    }

    //_ThreadPoolExecutor();
    while(1) {
        ThreadPoolExecutor pool = createExecutorBuilder()->setQueueSize(1)->setThreadNum(1)->newThreadPool();
        pool->shutdown();
        printf("---[TestThreadPoolExecutor Test {constructor2()} case1] [OK]--- \n");
        break;
    }


    //void shutdown();
    while(1) {
        ThreadPoolExecutor pool = createExecutorBuilder()->setQueueSize(100)->setThreadNum(100)->newThreadPool();
        pool->submit(createMyRunTest1());
        pool->shutdown();
        sleep(5);
        //if(!pool->isShutdown()) {
        //    printf("---[TestThreadPoolExecutor Test {shutdown()} case1] [FAILED]--- \n");
        //    break;
        //}

        Future task = pool->submit(createMyRunTest1());
        if(task != nullptr) {
            printf("---[TestThreadPoolExecutor Test {shutdown()} case2] [FAILED]--- \n");
            break;
        }

        int result = pool->execute(createMyRunTest1());
        if(result != -InvalidStatus) {
            printf("---[TestThreadPoolExecutor Test {shutdown()} case3] [FAILED]--- result is %d\n",result);
            break;
        }

        printf("---[TestThreadPoolExecutor Test {shutdown()} case4] [OK]--- \n");
        break;
    }

    //int awaitTermination(long timeout);
    while(1) {
        ThreadPoolExecutor pool = createExecutorBuilder()->setQueueSize(1)->setThreadNum(1)->newThreadPool();
        int result = pool->awaitTermination(1000);
        if(result != -InvalidStatus) {
            printf("---[TestThreadPoolExecutor Test {awaitTermination()} case1] [FAILED]--- \n");
            break;
        }
        printf("start awaitTermination test \n");
        runTest2Mutex = createMutex();
        runTest2Mutex->lock();

        pool->submit(createRunTest2());
		//printf("start at % ld \n",st(System)::currentTimeMillis());
        sleep(1);
		//printf("start end % ld \n",st(System)::currentTimeMillis());
        pool->shutdown();

        long current = st(System)::currentTimeMillis();
        result = pool->awaitTermination(5000);
        //printf("awaitTermination result is %d \n",result);
        if(result != -WaitTimeout) {
            printf("---[TestThreadPoolExecutor Test {awaitTermination()} case2] [FAILED]---,result is %d \n",result);
            break;
        }

        long current2 = st(System)::currentTimeMillis();
        //printf("current2 - current1 is %d \n",(current2 - current));
        if(current2 - current > 5015) {
            printf("---[TestThreadPoolExecutor Test {awaitTermination()} case3] [FAILED]--- \n");
            break;
        }

        printf("---[TestThreadPoolExecutor Test {awaitTermination()} case4] [OK]--- \n");
        runTest2Mutex->unlock();
        break;
    }


    //int awaitTermination(long timeout = 0);
    while(1) {
        ThreadPoolExecutor pool = createExecutorBuilder()->setQueueSize(100)->setThreadNum(100)->newThreadPool();
        //int result = pool->awaitTermination(0);
        //if(result != -InvalidStatus) {
        //    printf("---[TestThreadPoolExecutor Test {awaitTermination()} case5] [FAILED]--- \n");
        //    break;
        //}

        pool->submit(createMyRunTest1());
        pool->shutdown();

        long current = st(System)::currentTimeMillis();
        //printf("awaitTermination start test \n");
        int result = pool->awaitTermination(0);
        //printf("awaitTermination result is %d \n",result);
        if(result != 0) {
            printf("---[TestThreadPoolExecutor Test {awaitTermination()} case6] [FAILED]--- \n");
            break;
        }

        long current2 = st(System)::currentTimeMillis();
        //printf("current2 - current1 is %d \n",(current2 - current));
        if(current2 - current > 10005) {
            printf("---[TestThreadPoolExecutor Test {awaitTermination()} case7] [FAILED]--- \n");
            break;
        }

        printf("---[TestThreadPoolExecutor Test {awaitTermination()} case8] [OK]--- \n");
        break;
    }


    //int awaitTermination(long timeout = max);
    while(1) {
        ThreadPoolExecutor pool = createExecutorBuilder()->setQueueSize(100)->setThreadNum(100)->newThreadPool();
        pool->submit(createMyRunTest1());
        pool->shutdown();

        long current = st(System)::currentTimeMillis();
        pool->awaitTermination(100000);
        long v = st(System)::currentTimeMillis() - current;
        if(v > 10005) {
            printf("---[TestThreadPoolExecutor Test {awaitTermination()},v is %ld case9] [FAILED]--- \n",v);
            break;
        }

        printf("---[TestThreadPoolExecutor Test {awaitTermination()} case10] [OK]--- \n");
        break;
    }


    //int getThreadsNum();
    while(1) {
        ThreadPoolExecutor pool = createExecutorBuilder()->setQueueSize(100)->setThreadNum(100)->newThreadPool();
        if(pool->getThreadsNum() != 100) {
            printf("---[TestThreadPoolExecutor Test {getThreadsNum()} case1] [FAILED]--- \n");
            break;
        }
        pool->shutdown();
        printf("---[TestThreadPoolExecutor Test {getThreadsNum()} case2] [OK]--- \n");
        break;
    }

    //submit(Runnable task);
    while(1) {
        ThreadPoolExecutor pool = createExecutorBuilder()->setQueueSize(1)->setThreadNum(1)->newThreadPool();
        Future task = pool->submit(createMyRunTest1());
        if(task == nullptr) {
            printf("---[TestThreadPoolExecutor Test {submit()} case1] [FAILED]--- \n");
            break;
        }

        long current = st(System)::currentTimeMillis();
        Future task2 = pool->submit(createMyRunTest1());
        int v = st(System)::currentTimeMillis() - current;
        if(v >10005) {
            printf("---[TestThreadPoolExecutor Test {submit()} case2] [FAILED]--- \n");
            break;
        }
        pool->shutdown();
        printf("---[TestThreadPoolExecutor Test {submit()} case3] [OK]--- \n");
        break;
    }

}
