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

using namespace obotcha;

int runDestory = 1;

DECLARE_SIMPLE_CLASS(RunTest1) IMPLEMENTS(Runnable) {
public:
    void run() {
        printf("i am running \n");
        sleep(5);
    }

    ~_RunTest1() {
        printf("i am release \n");
        runDestory = 0;
    }
};


int runTest2V = 1;
DECLARE_SIMPLE_CLASS(RunTest2) IMPLEMENTS(Runnable) {
public:
    void run() {
        runTest2V = 100;
    }
};


Mutex runTest3Mutex;
DECLARE_SIMPLE_CLASS(RunTest3) IMPLEMENTS(Runnable) {
public:
    void run() {
        printf("RunTest2 start 1\n");
        runTest3Mutex->lock();
        printf("RunTest2 start 2\n");
    }
};


int main() {
    printf("---[TestFuture Test Start]--- \n");

    //wait(long t);
    while(1) {
        ExecutorService pool = st(Executors)::newFixedThreadPool(5,5);
        Future f = pool->submit(createRunTest1());
        long current = st(System)::currentTimeMillis();
        f->wait(2000);
        int v = st(System)::currentTimeMillis() - current;
        if(v >= 2005) {
            printf("---[TestFuture Test {wait(long t)} case1] [FAIL]--- \n");
            break;
        }

        printf("---[TestFuture Test {wait(long t)} case2] [Success]--- \n");
        break;
    }

    //wait(long t);
    while(1) {
        ExecutorService pool = st(Executors)::newFixedThreadPool(5,5);
        Future f = pool->submit(createRunTest1());
        long current = st(System)::currentTimeMillis();
        f->wait(12000);
        int v = st(System)::currentTimeMillis() - current;
        if(v >= 5005) {
            printf("---[TerunTest2VstFuture Test {wait(long t)} case3] [FAIL]--- \n");
            break;
        }

        printf("---[TestFuture Test {wait(long t)} case4] [Success]--- \n");
        break;
    }

    //void wait();
    while(1) {
        ExecutorService pool = st(Executors)::newFixedThreadPool(5,5);
        Future f = pool->submit(createRunTest1());
        long current = st(System)::currentTimeMillis();
        f->wait();
        int v = st(System)::currentTimeMillis() - current;
        if(v >= 5005) {
            printf("---[TestFuture Test {wait()} case1] [FAIL]--- \n");
            break;
        }

        printf("---[TestFuture Test {wait()} case4] [Success]--- \n");
        break;
    }

    //void cancel();
    while(1) {
        ExecutorService pool = st(Executors)::newFixedThreadPool(1,1);
        Future f1 = pool->submit(createRunTest1());
        Future f2 = pool->submit(createRunTest2());
        sleep(1);
        int ret = f1->cancel();
        int ret2 = f2->cancel();

        if(ret == 0) {
            printf("---[TestFuture Test {cancel()} case2] [FAIL]--- \n");
            break;
        }

        if(ret2 != 0) {
            printf("---[TestFuture Test {cancel()} case3] [FAIL]--- \n");
            break;
        }

        sleep(6);

        if(runTest2V == 100) {
            printf("---[TestFuture Test {cancel()} case4] [FAIL]--- \n");
            break;
        }

        printf("---[TestFuture Test {cancel()} case5] [Success]--- \n");
        break;
    }

    sleep(10);
}
