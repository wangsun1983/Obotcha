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
#include "Error.hpp"
#include "ThreadScheduledPoolExecutor.hpp"
#include "Long.hpp"

using namespace obotcha;

AtomicInteger myloopvalue = createAtomicInteger(0);

DECLARE_SIMPLE_CLASS(MyLoopSubmit) IMPLEMENTS(Runnable) {
public:

    void run() {
        myloopvalue->incrementAndGet();
    }

    void onInterrupt() {
        //printf("MyLoopSubmit interrupt \n");
    }
};

Mutex myloopsubmitMutex = createMutex("MyMutex");
ArrayList<long> currentTimeList = createArrayList<long>();

DECLARE_SIMPLE_CLASS(MyLoopTimeSubmit) IMPLEMENTS(Runnable) {
public:

    void run() {
        AutoLock l(myloopsubmitMutex);
        currentTimeList->add(st(System)::currentTimeMillis());
    }

    void onInterrupt() {
        //printf("MyLoopSubmit interrupt \n");
    }
};

int scheduleloopsubmit() {
    //test1
    ScheduledExecutorService pool = st(Executors)::newScheduledThreadPool();
    long time = st(System)::currentTimeMillis();
    for(int i = 0; i < 32*1024;i++) {
        pool->schedule(createMyLoopSubmit(),0);
    }
    printf("finish submit cost %ld \n",st(System)::currentTimeMillis() - time);


    sleep(1);
    if(myloopvalue->get() != 32*1024) {
        printf("---[ScheduledThreadPoolExecutor LoopSubmit case1],value is %d [FAIL]--- \n",myloopvalue->get());
    }
    pool->shutdown();

    //test2
    myloopvalue = createAtomicInteger(0);
    pool = st(Executors)::newScheduledThreadPool();
    for(int i = 0; i < 32*1024;i++) {
        pool->schedule(createMyLoopSubmit(),100);
    }

    sleep(5);

    if(myloopvalue->get() != 32*1024) {
        printf("---[ScheduledThreadPoolExecutor LoopSubmit case2],value is %d [FAIL]--- \n",myloopvalue->get());
    }
    pool->shutdown();
    
#if 0 //need test
    //test3
    pool = st(Executors)::newScheduledThreadPool();
    long time = st(System)::currentTimeMillis();

    for(int i = 0; i < 32*1024;i++) {
        pool->schedule(createMyLoopTimeSubmit(),100);
    }

    sleep(5);
    if(currentTimeList->size() != 32*1024) {
        printf("---[ScheduledThreadPoolExecutor LoopSubmit case3],size is %d [FAIL]--- \n",currentTimeList->size());
    }

    for(int i = 0;i < 32*1024;i++) {
        long v = currentTimeList->get(i);
        if((v - time) > 200) {
           printf("---[ScheduledThreadPoolExecutor LoopSubmit case4],i is %d,time is %ld [FAIL]--- \n",i,v-time);
           //break;
        }
    }
#endif
    printf("---[ScheduledThreadPoolExecutor LoopSubmit case100] [Success]--- \n");
}
