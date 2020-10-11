#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "System.hpp"
#include "ThreadPriorityPoolExecutor.hpp"
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
        AutoLock ll(mMutex);
        //printf("i am wait \n");
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
    _MyShutdownRunTest4(ThreadPriorityPoolExecutor p) {
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
    ThreadPriorityPoolExecutor mPool;
    long interval;
};



int testThreadShutdown() {

    while(1) {
        ThreadPriorityPoolExecutor pool123 = createThreadPriorityPoolExecutor();
        MyShutdownRunTest2 run = createMyShutdownRunTest2();
        pool123->submit(run);
        pool123->submit(run);
        pool123->submit(run);
        pool123->submit(run);
        pool123->submit(run);
        pool123->shutdown();
        sleep(1);
        if(run->getCount() != 5) {
            printf("---[ThreadPriorityPoolExecutor Test {shutdown()} special case4],count is %d [FAIL]--- \n",run->getCount());
            break;
        }

        printf("---[ThreadPriorityPoolExecutor Test {shutdown()} special case5] [Success]--- \n");
        break;
    }

    while(1) {
        ThreadPriorityPoolExecutor pool = createThreadPriorityPoolExecutor();
        long t = st(System)::currentTimeMillis();
        pool->awaitTermination(1000);
        long current = st(System)::currentTimeMillis();
        if((current - t) > 1) {
            printf("---[ThreadPriorityPoolExecutor Test {shutdown()} special case6] [FAIL]--- \n");
            break;
        }

        pool->shutdown();
        printf("---[ThreadPriorityPoolExecutor Test {shutdown()} special case7] [Success]--- \n");
        break;
    }

    while(1) {
        ThreadPriorityPoolExecutor pool = createThreadPriorityPoolExecutor();
        pool->submit(createMyShutdownRunTest3());
        long t = st(System)::currentTimeMillis();
        pool->shutdown();

        int result = pool->awaitTermination(1000);
        long current = st(System)::currentTimeMillis();
        if((current - t) > 1 || result < 0) {
            printf("---[ThreadPriorityPoolExecutor Test {shutdown()} special case8] [FAIL]--- \n");
            break;
        }

        printf("---[ThreadPriorityPoolExecutor Test {shutdown()} special case9] [Success]--- \n");
        break;
    }

    return 0;

}
