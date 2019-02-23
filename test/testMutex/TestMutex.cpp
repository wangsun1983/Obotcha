#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "Integer.hpp"
#include "AutoMutex.hpp"


DECLARE_CLASS(Thread1) IMPLEMENTS(Runnable) {
public:

    Thread1(sp<Mutex> mutex) {
        //cond = condition;
        mutex_t = mutex;
    }

    void run() {
        printf("Thread1 start \n");
        AutoMutex l(mutex_t);
        //mutex_t->lock();
        //cond->wait(mutex_t);
        printf("Thread1 goto sleep \n");
        sleep(15);
        //mutex_t->unlock();
        printf("Thread1 end \n");
    }

private:
    //Condition *cond;
    sp<Mutex> mutex_t;
};

DECLARE_CLASS(Thread2) IMPLEMENTS(Runnable) {
public:

    Thread2(sp<Mutex> mutex) {
      mutex_t = mutex;
    }

    void run() {
        printf("Thread2 start \n");
        //cond->notify();
        AutoMutex l(mutex_t);
        //mutex_t->lock();
        printf("Thread2 trace \n");
        //mutex_t->unlock();
        printf("Thread2 end \n");
    }

private:
    sp<Mutex> mutex_t;
};

int main() {
    //Condition cond;
    sp<Mutex> mutex = new Mutex();

    sp<Thread> mThread1 = new Thread(new Thread1(mutex));
    mThread1->start();
    printf("start sleep \n");
    sleep(2);
    printf("start sleep complete,start produceRunn \n");
    sp<Thread> mThread2 = new Thread(new Thread2(mutex));
    mThread2->start();

    while(1) {
        usleep(1000);
    }
}
