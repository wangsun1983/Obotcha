#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "AutoLock.hpp"
#include "Integer.hpp"


DECLARE_CLASS(ConsumeRunn) IMPLEMENTS(Runnable) {
public:

    ConsumeRunn(Condition *condition,sp<Mutex> m) {
        cond = condition;
        mutex_t = m;
    }

    void run() {
        printf("ConsumeRunn start \n");
        //mutex_t.lock();
        AutoLock l(mutex_t);

        cond->wait(mutex_t);
        //mutex_t.unlock();
        printf("ConsumeRunn end \n");
    }

private:
    Condition *cond;
    sp<Mutex> mutex_t;
};

DECLARE_CLASS(ProduceRunn) IMPLEMENTS(Runnable) {
public:

    ProduceRunn(Condition *condition,sp<Mutex> m) {
      cond = condition;
      mutex_t = m;
    }

    void run() {
        printf("ProduceRunn start \n");
        AutoLock l(mutex_t);
        cond->notify();
        printf("ProduceRunn end \n");
    }

private:
    Condition *cond;
    sp<Mutex> mutex_t;
};

int main() {
    Condition cond;
    sp<Mutex> mutex_t = new Mutex();

    sp<Thread> mThread1 = new Thread(new ConsumeRunn(&cond,mutex_t));
    mThread1->start();
    printf("start sleep \n");
    sleep(10);
    printf("start sleep complete,start produceRunn \n");
    sp<Thread> mThread2 = new Thread(new ProduceRunn(&cond,mutex_t));
    mThread2->start();

    while(1) {
        usleep(1000);
    }
}
