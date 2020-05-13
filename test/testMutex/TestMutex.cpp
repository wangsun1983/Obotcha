#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "Integer.hpp"
#include "AutoLock.hpp"
#include "Mutex.hpp"
#include "System.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyRun1) IMPLEMENTS(Runnable) {
public:

    _MyRun1(Mutex mutex) {
        //cond = condition;
        mutex_t = mutex;
    }

    void run() {
        //printf("Thread1 start \n");
        AutoLock l(mutex_t);
        //mutex_t->lock();
        //cond->wait(mutex_t);
        //printf("Thread1 goto sleep \n");
        sleep(5);
        //mutex_t->unlock();
        //printf("Thread1 end \n");
    }

private:
    //Condition *cond;
    Mutex mutex_t;
};

DECLARE_SIMPLE_CLASS(MyRun2) IMPLEMENTS(Runnable) {
public:

    _MyRun2(Mutex mutex) {
      mutex_t = mutex;
    }

    void run() {
        //printf("Thread2 start \n");
        //cond->notify();
        AutoLock l(mutex_t);
        //mutex_t->lock();
        //printf("Thread2 trace \n");
        //mutex_t->unlock();
        //printf("Thread2 end \n");
    }

private:
    Mutex mutex_t;
};

#if 0
DECLARE_SIMPLE_CLASS(MyRun3) IMPLEMENTS(Runnable) {
public:

    _MyRun3(Mutex mutex) {
      mutex_t = mutex;
    }

    void run() {
        //printf("Thread2 start \n");
        //cond->notify();
        AutoLock l(mutex_t,2000);
        //mutex_t->lock();
        //printf("Thread2 trace \n");
        //mutex_t->unlock();
        //printf("Thread2 end \n");
    }

private:
    Mutex mutex_t;
};
#endif

DECLARE_SIMPLE_CLASS(MyRun4) IMPLEMENTS(Runnable) {
public:

    _MyRun4(Mutex mutex) {
      mutex_t = mutex;
    }

    void run() {
        //printf("Thread2 start \n");
        //cond->notify();
        //AutoLock l(mutex_t,2000);
        mutex_t->trylock();
        //mutex_t->lock();
        //printf("Thread2 trace \n");
        //mutex_t->unlock();
        //printf("Thread2 end \n");
    }

private:
    Mutex mutex_t;
};

int testMutexNormal() {
    //Mutex()
    while(1) {
        Mutex mutex = createMutex();
        printf("---[TestMutex Test {construct()} case1] [OK]--- \n");
        break;
    }

    //Mutex(String)
    while(1) {
        Mutex mutex = createMutex("test");
        if(!mutex->toString()->equals("test")) {
            printf("---[TestMutex Test {construct(String)} case1] [FAIL]--- \n");
            break;
        }

        printf("---[TestMutex Test {construct(String)} case2] [OK]--- \n");
        break;
    }

    //lock()
    while(1) {
        Mutex mutex = createMutex("test");
        Thread mThread1 = createThread(createMyRun1(mutex));//new Thread(new Thread1(mutex));
        mThread1->start();
        long current = st(System)::currentTimeMillis();
        sleep(1);

        Thread mThread2 = createThread(createMyRun2(mutex));
        mThread2->start();
        mThread2->join();
        int v = st(System)::currentTimeMillis() - current;
        if(v >5005) {
            printf("---[TestMutex Test {lock()} case1] [FAIL]--- \n");
            break;
        }

        printf("---[TestMutex Test {lock()} case2] [OK]--- \n");
        break;
    }

#if 0
    //lock(long)
    while(1) {
        Mutex mutex = createMutex("test");
        Thread mThread1 = createThread(createMyRun1(mutex));//new Thread(new Thread1(mutex));
        mThread1->start();
        sleep(1);
        long current = st(System)::currentTimeMillis();
        Thread mThread2 = createThread(createMyRun3(mutex));
        mThread2->start();
        int v = st(System)::currentTimeMillis() - current;
        if(v > 2005) {
            printf("---[TestMutex Test {lock(long)} case1] [FAIL]--- \n");
            break;
        }

        printf("---[TestMutex Test {lock(long)} case2] [OK]--- \n");
        break;
    }
#endif

    //unlock()
    while(1) {
        Mutex t = createMutex();
        int ret = t->unlock();
        if(ret == 0) {
            printf("---[TestMutex Test {unlock()} case1] [FAIL]--- \n");
            break;
        }

        printf("---[TestMutex Test {unlock()} case2] [OK]--- \n");
        break;
    }

    //trylock()
    while(1) {
        Mutex mutex = createMutex("test");
        Thread mThread1 = createThread(createMyRun1(mutex));//new Thread(new Thread1(mutex));
        mThread1->start();
        sleep(1);
        long current = st(System)::currentTimeMillis();
        Thread mThread2 = createThread(createMyRun4(mutex));
        mThread2->start();
        mThread2->join();

        int v = st(System)::currentTimeMillis() - current;
        //printf("v is %d \n",v);
        if(v > 5) {
            printf("---[TestMutex Test {trylock()} case1] [FAIL]--- \n");
            break;
        }

        printf("---[TestMutex Test {trylock()} case2] [OK]--- \n");
        break;
    }

    sleep(10);
}
