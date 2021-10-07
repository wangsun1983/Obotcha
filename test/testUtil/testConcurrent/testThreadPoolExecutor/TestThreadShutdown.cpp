#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "System.hpp"
#include "ThreadPoolExecutor.hpp"
#include "ExecutorBuilder.hpp"
#include "Error.hpp"

using namespace obotcha;

DECLARE_CLASS(MyShutdownRunTest1) IMPLEMENTS(Runnable) {
public:
    void run() {
        //printf("i am running123 \n");
        sleep(10);
    }

    void onInterrupt() {
    }
};

DECLARE_CLASS(MyShutdownRunTest2) IMPLEMENTS(Runnable) {
public:
    _MyShutdownRunTest2() {
        mMutex = createMutex();
        count = 0;
    }

    void run() {
        //printf("i am running123 \n");
        sleep(10);
    }

    void onInterrupt() {
        AutoLock ll(mMutex);
        count++;
    }

    int getCount() {
        return count;
    }

private:
    Mutex mMutex;
    int count;
};

DECLARE_CLASS(MyShutdownRunTest3) IMPLEMENTS(Runnable) {
public:
    void run() {

    }
};

DECLARE_CLASS(MyShutdownRunTest4) IMPLEMENTS(Thread) {
public:
    _MyShutdownRunTest4(ThreadPoolExecutor p) {
        mPool = p;
    }

    void run() {
        long start = st(System)::currentTimeMillis();
        mPool->awaitTermination(10000);
        long end = st(System)::currentTimeMillis();
        interval = end - start;
    }

    long getInterval() {
        return interval;
    }

private:
    ThreadPoolExecutor mPool;
    long interval;
};

void testThreadShutdown() {


    //TestThread onInterrupt case1
    while(1) {
        ThreadPoolExecutor pool = createExecutorBuilder()->newThreadPool();
        pool->shutdown();
        int ret = pool->shutdown();

        if(ret != -AlreadyDestroy) {
            printf("---[ThreadPoolExecutor Test {shutdown()} special case1] [FAIL]---,ret is %d \n",ret);
            break;
        }

        auto mtask = pool->submit(createMyShutdownRunTest1());
        if(mtask != nullptr) {
            printf("---[ThreadPoolExecutor Test {shutdown()} special case2] [FAIL]--- \n");
            break;
        }

        printf("---[ThreadPoolExecutor Test {shutdown()} special case3] [OK]--- \n");
        break;
    }

    while(1) {
        ThreadPoolExecutor pool = createThreadPoolExecutor(128,1);
        MyShutdownRunTest2 run = createMyShutdownRunTest2();
        pool->submit(run);
        pool->submit(run);
        pool->submit(run);
        pool->submit(run);
        pool->submit(run);
        sleep(1);
        pool->shutdown();
        sleep(1);
        if(run->getCount() != 4) {
            printf("---[ThreadPoolExecutor Test {shutdown()} special case4,run->getCount is %d ] [FAIL]--- \n",run->getCount());
            break;
        }
        printf("---[ThreadPoolExecutor Test {shutdown()} special case5] [OK]--- \n");
        break;
    }

    while(1) {
        ThreadPoolExecutor pool = createExecutorBuilder()->newThreadPool();
        long t = st(System)::currentTimeMillis();
        pool->awaitTermination(1000);
        long current = st(System)::currentTimeMillis();
        if((current - t) > 1) {
            printf("---[ThreadPoolExecutor Test {shutdown()} special case6, interval is %ld] [FAIL]--- \n",current - t);
            break;
        }

        pool->shutdown();
        printf("---[ThreadPoolExecutor Test {shutdown()} special case7] [OK]--- \n");
        break;
    }

    while(1) {
        ThreadPoolExecutor pool = createExecutorBuilder()->newThreadPool();
        pool->submit(createMyShutdownRunTest3());
        pool->shutdown();
        long t = st(System)::currentTimeMillis();
        int result = pool->awaitTermination(1000);
        long current = st(System)::currentTimeMillis();
        if((current - t) > 10 || result < 0) {
            printf("---[ThreadPoolExecutor Test {shutdown()} special case8] [FAIL]---,interval is %ld,result is %d \n",current - t,result);
            break;
        }

        printf("---[ThreadPoolExecutor Test {shutdown()} special case9] [OK]--- \n");
        break;
    }

}
