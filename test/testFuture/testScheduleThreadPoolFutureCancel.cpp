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


DECLARE_SIMPLE_CLASS(TestScheduleCancelRun1) IMPLEMENTS(Runnable) {
public:
    _TestScheduleCancelRun1() {
        interrupt = 0;
        value = 0;
    }

    void run() {
        printf("i am running trace1\n");
        sleep(2);
        value = 1;
        printf("i am running trace2\n");
    }

    void onInterrupt() {
        printf("i am interrupt trace1\n");
        interrupt = 1;
        printf("i am interrupt trace2\n");
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

DECLARE_SIMPLE_CLASS(TestScheduleCancelRun2) IMPLEMENTS(Runnable) {
public:
    _TestScheduleCancelRun2() {
        interrupt = 0;
        value = 0;
    }

    void run() {
        sleep(2);
        value++;
        printf("run thread:%d finished \n",count);
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

    void setCount(int v) {
        count = v;
    }

    int getCount() {
        return count;
    }

private:
    int value;
    int interrupt;
    int count;
};

int testThreadScheduleFutureCancel() {
    //threadExecutorPool
#if 0  
    while(1) {
        ExecutorService pool = st(Executors)::newScheduledThreadPool();
        TestScheduleCancelRun1 run1 = createTestScheduleCancelRun1();
        Future f = pool->submit(run1);
        sleep(1);
        f->cancel();
        sleep(5);
        if(run1->getValue() == 1 || run1->getInterrupt() != 1) {
            printf("---[TestFuture ScheduledThreadPool Test {cancel()} case1] [FAIL],val is %d,interrupt is %d--- \n",run1->getValue(),run1->getInterrupt());
            break;
        }

        printf("---[TestFuture ScheduledThreadPool Test {cancel()} case2] [Success]--- \n");
        break;
    }
 #endif   

    while(1) {
        ExecutorService pool = st(Executors)::newScheduledThreadPool();
        ArrayList<Future> futurelist = createArrayList<Future>();
        for(int i = 0;i<50;i++) {
            Future f = pool->submit(createTestScheduleCancelRun1());
            futurelist->add(f);
        }

        //for(int j = 0;j<50;j++) {
        printf("start test cancel \n");
        ListIterator<Future> iterator = futurelist->getIterator();
        while(iterator->hasValue()) {
            Future f = iterator->getValue();
            f->cancel();
            iterator->next();
        }
        //}
        

        sleep(1);

        printf("pool count is %d \n",pool->getStrongCount());
        printf("---[TestFuture ScheduledThreadPool Test {cancel()} case3] [Success]--- \n");
        break;
    }



 

#if 0
    while(1) {
        ExecutorService pool = st(Executors)::newScheduledThreadPool();
        ArrayList<Future> futurelist = createArrayList<Future>();
        for(int i = 0;i<50;i++) {
            Future f = pool->submit(createTestScheduleCancelRun1());
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
        printf("---[TestFuture ScheduledThreadPool Test {cancel()} case4] [Success]--- \n");
        break;
    }


    while(1) {
        ExecutorService pool = st(Executors)::newScheduledThreadPool();
        ArrayList<Future> futurelist = createArrayList<Future>();
        for(int i = 0;i<55;i++) {
            Future f = pool->submit(createTestScheduleCancelRun1());
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
        Future f1 = pool->submit(createTestScheduleCancelRun1());
        Future f2 = pool->submit(createTestScheduleCancelRun1());
        long end = st(System)::currentTimeMillis();
        if((end - start) > 10) {
            printf("---[TestFuture ScheduledThreadPool Test {cancel()} case5] [Fail],%d --- \n",end-start);
            break;
        }

        printf("---[TestFuture ScheduledThreadPool Test {cancel()} case6] [Success]--- \n");
        break;
    }


    while(1) {
        ExecutorService pool = st(Executors)::newScheduledThreadPool();
        ArrayList<Future> futurelist = createArrayList<Future>();
        ArrayList<TestScheduleCancelRun2> runlist = createArrayList<TestScheduleCancelRun2>();
        for(int i = 0;i<55;i++) {
            TestScheduleCancelRun2 run2 = createTestScheduleCancelRun2();
            run2->setCount(i);
            runlist->add(run2);
            Future f = pool->submit(run2);
            futurelist->add(f);
        }
        sleep(1);
        printf("start stop future \n");
        //for(int j = 0;j<55;j++) {
            ListIterator<Future> iterator = futurelist->getIterator();
            while(iterator->hasValue()) {
                Future f = iterator->getValue();
                f->cancel();
                iterator->next();
            }
        //}

        sleep(100);

        
        ListIterator<TestScheduleCancelRun2> iterator2 = runlist->getIterator();
        while(iterator2->hasValue()) {
            TestScheduleCancelRun2 run_2 = iterator2->getValue();
            if(run_2->getValue() != 0) {
                printf("---[TestFuture ScheduledThreadPool Test {cancel()} case7] [Fail],count is %d,value is %d --- \n",run_2->getCount(),run_2->getValue());
                //break;
            }
            iterator2->next();
        }

        printf("---[TestFuture ScheduledThreadPool Test {cancel()} case8] [Success] --- \n");
        break;
       
    }
#endif
}
