#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoMutex.hpp"
#include "System.hpp"
#include "PriorityPoolExecutor.hpp"
#include "Error.hpp"
#include "Executors.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyShutdownRunTest1) IMPLEMENTS(Runnable) {
public:
    void run() {
        //printf("i am running123 \n");
        sleep(10);
    }

    void onInterrupt() {
    }
};

DECLARE_SIMPLE_CLASS(MyShutdownRunTest2) IMPLEMENTS(Runnable) {
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
        AutoMutex ll(mMutex);
        count++;
    }

    int getCount() {
        return count;
    }

private:
    Mutex mMutex;
    int count;
};

DECLARE_SIMPLE_CLASS(MyShutdownRunTest3) IMPLEMENTS(Runnable) {
public:
    void run() {

    }
};

DECLARE_SIMPLE_CLASS(MyShutdownRunTest4) IMPLEMENTS(Thread) {
public:
    _MyShutdownRunTest4(PriorityPoolExecutor p) {
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
    PriorityPoolExecutor mPool;
    long interval;
};



int testThreadShutdown() {

    //TestThread onInterrupt case1
    while(1) {
        ExecutorService pool = st(Executors)::newPriorityThreadPool();
        pool->shutdown();
        int ret = pool->shutdown();

        if(ret != 0) {
            printf("---[PriorityPoolExecutor Test {shutdown()} special case1] [FAIL]--- \n");
            break;
        }

        auto mtask = pool->submit(createMyShutdownRunTest1());
        if(mtask != nullptr) {
            printf("---[PriorityPoolExecutor Test {shutdown()} special case2] [FAIL]--- \n");
            break;
        }

        printf("---[PriorityPoolExecutor Test {shutdown()} special case3] [Success]--- \n");
        break;
    }

    while(1) {
        PriorityPoolExecutor pool = createPriorityPoolExecutor();
        MyShutdownRunTest2 run = createMyShutdownRunTest2();
        pool->submit(run);
        pool->submit(run);
        pool->submit(run);
        pool->submit(run);
        pool->submit(run);
        pool->shutdown();
        sleep(1);
        if(run->getCount() != 5) {
            printf("---[PriorityPoolExecutor Test {shutdown()} special case4] [FAIL]--- \n");
            break;
        }

        printf("---[PriorityPoolExecutor Test {shutdown()} special case5] [Success]--- \n");
        break;
    }

    while(1) {
        PriorityPoolExecutor pool = createPriorityPoolExecutor();
        long t = st(System)::currentTimeMillis();
        pool->awaitTermination(1000);
        long current = st(System)::currentTimeMillis();
        if((current - t) > 1) {
            printf("---[PriorityPoolExecutor Test {shutdown()} special case6] [FAIL]--- \n");
            break;
        }

        pool->shutdown();
        printf("---[PriorityPoolExecutor Test {shutdown()} special case7] [Success]--- \n");
        break;
    }

    while(1) {
        PriorityPoolExecutor pool = createPriorityPoolExecutor();
        pool->submit(createMyShutdownRunTest3());
        long t = st(System)::currentTimeMillis();
        pool->shutdown();

        int result = pool->awaitTermination(1000);
        long current = st(System)::currentTimeMillis();
        if((current - t) > 1 || result < 0) {
            printf("---[PriorityPoolExecutor Test {shutdown()} special case8] [FAIL]--- \n");
            break;
        }

        printf("---[PriorityPoolExecutor Test {shutdown()} special case9] [Success]--- \n");
        break;
    }

    return 0;

}
