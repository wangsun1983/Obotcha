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


DECLARE_SIMPLE_CLASS(TestCancelRun1) IMPLEMENTS(Runnable) {
public:
    _TestCancelRun1() {
        interrupt = 0;
        value = 0;
    }

    void run() {
        sleep(2);
        value = 1;
    }

    void onInterrupt() {
        interrupt = 1;
    }

    int getValue() {
        return value;
    }

    int getInterrupt() {
        return interrupt;
    }

private:
    int value;
    int interrupt; 
};

DECLARE_SIMPLE_CLASS(TestCancelRun2) IMPLEMENTS(Runnable) {
public:
    _TestCancelRun2() {
        interrupt = 0;
        value = 0;
    }

    void run() {
        sleep(2);
        value++;
    }

    void onInterrupt() {
        interrupt = 1;
    }

    int getValue() {
        return value;
    }

    int getInterrupt() {
        return interrupt;
    }

private:
    int value;
    int interrupt; 
};

int testThreadExecutorPoolFutureCancel() {
    //threadExecutorPool
#if 0    
    while(1) {
        ExecutorService pool = st(Executors)::newFixedThreadPool(5,5);
        TestCancelRun1 run1 = createTestCancelRun1();
        Future f = pool->submit(run1);
        f->cancel();
        sleep(5);
        if(run1->getValue() == 1 || run1->getInterrupt() != 1) {
            printf("---[TestFuture ExecutorPool Test {cancel()} case1] [FAIL]--- \n");
            break;
        }
        pool->shutdown();
        printf("---[TestFuture ExecutorPool Test {cancel()} case2] [Success]--- \n");
        break;
    }
#endif

    while(1) {
        ExecutorService pool = st(Executors)::newFixedThreadPool(50,5);
        ArrayList<Future> futurelist = createArrayList<Future>();
        for(int i = 0;i<50;i++) {
            Future f = pool->submit(createTestCancelRun1());
            futurelist->add(f);
        }

        for(int j = 0;j<50;j++) {
            ListIterator<Future> iterator = futurelist->getIterator();
            while(iterator->hasValue()) {
                Future f = iterator->getValue();
                f->cancel();
                iterator->next();
            }
        }
        
        sleep(1);
        pool->shutdown();
        printf("---[TestFuture ExecutorPool Test {cancel()} case3] [Success]--- \n");
        break;
    }

#if 0
    while(1) {
        ExecutorService pool = st(Executors)::newFixedThreadPool(50,5);
        ArrayList<Future> futurelist = createArrayList<Future>();
        for(int i = 0;i<50;i++) {
            Future f = pool->submit(createTestCancelRun1());
            futurelist->add(f);
        }

        pool->shutdown();

        for(int j = 0;j<50;j++) {
            ListIterator<Future> iterator = futurelist->getIterator();
            while(iterator->hasValue()) {
                Future f = iterator->getValue();
                f->cancel();
                iterator->next();
            }
        }
        
        sleep(1);
        pool->shutdown();
        printf("---[TestFuture ExecutorPool Test {cancel()} case4] [Success]--- \n");
        break;
    }


    while(1) {
        ExecutorService pool = st(Executors)::newFixedThreadPool(50,5);
        ArrayList<Future> futurelist = createArrayList<Future>();
        for(int i = 0;i<55;i++) {
            Future f = pool->submit(createTestCancelRun1());
            futurelist->add(f);
        }

        for(int j = 0;j<50;j++) {
            ListIterator<Future> iterator = futurelist->getIterator();
            while(iterator->hasValue()) {
                Future f = iterator->getValue();
                f->cancel();
                iterator->next();
            }
        }

        long start = st(System)::currentTimeMillis();
        //for(int i = 0;i<50;i++) {
        printf("submit testcancel run1 \n");
        Future f1 = pool->submit(createTestCancelRun1());
        Future f2 = pool->submit(createTestCancelRun1());
        long end = st(System)::currentTimeMillis();
        if((end - start) > 10) {
            printf("---[TestFuture ExecutorPool Test {cancel()} case5] [Fail],%d --- \n",end-start);
            break;
        }
        pool->shutdown();
        printf("---[TestFuture ExecutorPool Test {cancel()} case6] [Success]--- \n");
        break;
    }

    while(1) {
        ExecutorService pool = st(Executors)::newFixedThreadPool(50,5);
        ArrayList<Future> futurelist = createArrayList<Future>();
        ArrayList<TestCancelRun2> runlist = createArrayList<TestCancelRun2>();
        for(int i = 0;i<55;i++) {
            TestCancelRun2 run2 = createTestCancelRun2();
            runlist->add(run2);
            Future f = pool->submit(run2);
            futurelist->add(f);
        }
        sleep(1);

        //for(int j = 0;j<50;j++) {
            ListIterator<Future> iterator = futurelist->getIterator();
            while(iterator->hasValue()) {
                Future f = iterator->getValue();
                f->cancel();
                iterator->next();
            }
        //}

        sleep(100);

        for(int j = 0;j<50;j++) {
            ListIterator<TestCancelRun2> iterator = runlist->getIterator();
            TestCancelRun2 run_2 = iterator->getValue();
            if(run_2->getValue() != 0) {
                printf("---[TestFuture ExecutorPool Test {cancel()} case7] [Fail] --- \n");
                break;
            }
            iterator->next();
        }
        pool->shutdown();
        printf("---[TestFuture ExecutorPool Test {cancel()} case8] [Success] --- \n");
        break;
       
    }
#endif   
}
