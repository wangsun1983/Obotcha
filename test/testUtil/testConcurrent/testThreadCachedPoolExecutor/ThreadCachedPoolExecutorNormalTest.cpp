#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ThreadCachedPoolExecutor.hpp"
#include "Integer.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "AutoClose.hpp"
#include "ExecutorBuilder.hpp"

using namespace obotcha;

int runDestory = 1;
DECLARE_CLASS(RunTest1) IMPLEMENTS(Runnable) {
public:
    void run() {
        printf("run test1 start 1\n");
        try {
            st(Thread)::interruptableSleep(10*1000);
        } catch(InterruptedException &e){
            printf("run test1 start 1_1 \n");
        }
        printf("run test1 start 2\n");
    }

    void onInterrupt() {
    }

    ~_RunTest1() {
        printf("RunnTest1 release \n");
        runDestory = 0;
    }
};

Mutex runTest2Mutex;
DECLARE_CLASS(RunTest2) IMPLEMENTS(Runnable) {
public:
    void run() {
        printf("abc,runTest2Mutex lock \n");
        runTest2Mutex->lock();
        printf("abc,runTest2Mutex lock2 \n");
    }

    void onInterrupt() {
        printf("RunTest2 onInterrupt!!! \n");
    }
};


int normalTest() {
    printf("---[TestCachedPoolExecutor Test Start]--- \n");
#if 0
    while(1) {
        ThreadCachedPoolExecutor pool = createExecutorBuilder()
                                        ->setQueueSize(1)
                                        ->setMinThreadNum(1)
                                        ->setMaxThreadNum(2)
                                        ->setTimeout(60*1000)
                                        ->newCachedThreadPool();

        pool->shutdown();
        printf("---[TestCachedPoolExecutor Test {constructor()} case1] [Success]--- \n");
        break;
    }



    //_ThreadCachedPoolExecutor(int maxthreadnum,long timeout);
    while(1) {
        ThreadCachedPoolExecutor pool = createExecutorBuilder()
                                        ->setMaxThreadNum(2)
                                        ->setTimeout(60*1000)
                                        ->newCachedThreadPool();

        printf("---[TestCachedPoolExecutor Test {constructor2()} case2] [Success]--- \n");
        pool->shutdown();
        break;
    }

    //_ThreadCachedPoolExecutor();
    while(1) {
        ThreadCachedPoolExecutor pool = createExecutorBuilder()->newCachedThreadPool();
        pool->shutdown();
        printf("---[TestCachedPoolExecutor Test {constructor2()} case3] [Success]--- \n");
        break;
    }


    //void shutdown();
    while(1) {
        ThreadCachedPoolExecutor pool = createExecutorBuilder()->newCachedThreadPool();
        pool->submit(createRunTest1());
        sleep(1);

        pool->shutdown();

        sleep(5);
        if(!pool->isTerminated()) {
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
        ThreadCachedPoolExecutor pool = createExecutorBuilder()->newCachedThreadPool();

        int result = pool->awaitTermination(1000);
        if(result != -InvalidStatus) {
            printf("---[TestCachedPoolExecutor Test {awaitTermination()} case1] [FAIL]---,result is %d \n",result);
            break;
        }

        runTest2Mutex = createMutex();
        runTest2Mutex->lock();

        pool->submit(createRunTest2());
        sleep(1);
        pool->shutdown();

        long current = st(System)::currentTimeMillis();
        printf("start wait complete \n");
        result = pool->awaitTermination(5000);
        if(result != -WaitTimeout) {
            printf("---[TestCachedPoolExecutor Test {awaitTermination()} case2] [FAIL]---,result is %d \n",result);
            runTest2Mutex->unlock();
            pool->shutdown();
            break;
        }
        long current2 = st(System)::currentTimeMillis();
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
#endif

    //int awaitTermination(long timeout = 0);
    while(1) {
        ThreadCachedPoolExecutor pool = createExecutorBuilder()->newCachedThreadPool();

        //int result = pool->awaitTermination(0);
        //if(result != -InvalidStatus) {
        //    printf("---[TestCachedPoolExecutor Test {awaitTermination()} case5] [FAIL]--- \n");
        //    pool->shutdown();
        //    break;
        //}

        pool->submit(createRunTest1());
        pool->shutdown();

        long current = st(System)::currentTimeMillis();
        int result = pool->awaitTermination(0);
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

#if 0
    //int awaitTermination(long timeout = max);
    while(1) {
        ThreadCachedPoolExecutor pool = createExecutorBuilder()->newCachedThreadPool();

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
        ThreadCachedPoolExecutor pool = createExecutorBuilder()->newCachedThreadPool();

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
        ThreadCachedPoolExecutor pool = createExecutorBuilder()->newCachedThreadPool();

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
        ThreadCachedPoolExecutor pool = createExecutorBuilder()->newCachedThreadPool();
        printf("start submit task \n");
        Future task = pool->submit(createRunTest1());
        sleep(1);
        printf("start submit task2 \n");
        int num = pool->getThreadsNum();
        printf("start submit task3 \n");
        if(num != 1) {
            printf("---[TestCachedPoolExecutor Test {submit()} case4] [FAIL]---, num is %d\n",num);
            break;
        }
        printf("start submit task3_1 \n");
        sleep(100);
        printf("start submit task4 \n");
        if(pool->getThreadsNum() != 0) {
            printf("---[TestCachedPoolExecutor Test {submit()} case5] [FAIL]---,pool->getThreadsNum() is %d \n",pool->getThreadsNum());
            break;
        }
        printf("start submit task5 \n");
        pool->shutdown();
        printf("---[TestCachedPoolExecutor Test {submit()} case6] [Success]--- \n");
        break;
    }
#endif
    sleep(1);

}
