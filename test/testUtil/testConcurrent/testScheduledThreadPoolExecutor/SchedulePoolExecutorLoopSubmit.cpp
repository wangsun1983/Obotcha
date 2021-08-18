#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ThreadScheduledPoolExecutor.hpp"
#include "Integer.hpp"
#include "ExecutorBuilder.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "ThreadScheduledPoolExecutor.hpp"
#include "Long.hpp"

using namespace obotcha;

AtomicInteger myloopvalue = createAtomicInteger(0);

DECLARE_CLASS(MyLoopSubmit) IMPLEMENTS(Runnable) {
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

DECLARE_CLASS(MyLoopTimeSubmit) IMPLEMENTS(Runnable) {
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
    ThreadScheduledPoolExecutor pool = createExecutorBuilder()->newScheduledThreadPool();
    long time = st(System)::currentTimeMillis();
    for(int i = 0; i < 32*1024;i++) {
        pool->schedule(0,createMyLoopSubmit());
    }
    printf("finish submit cost %ld \n",st(System)::currentTimeMillis() - time);


    sleep(1);
    if(myloopvalue->get() != 32*1024) {
        printf("---[ScheduledThreadPoolExecutor LoopSubmit case1],value is %d [FAIL]--- \n",myloopvalue->get());
    }
    pool->shutdown();

    //test2
    myloopvalue = createAtomicInteger(0);
    pool = createExecutorBuilder()->newScheduledThreadPool();
    for(int i = 0; i < 32*1024;i++) {
        pool->schedule(100,createMyLoopSubmit());
    }

    sleep(5);

    if(myloopvalue->get() != 32*1024) {
        printf("---[ScheduledThreadPoolExecutor LoopSubmit case2],value is %d [FAIL]--- \n",myloopvalue->get());
    }
    pool->shutdown();
    
#if 0 //need test
    //test3
    pool = createExecutorBuilder()->newScheduledThreadPool();
    time = st(System)::currentTimeMillis();

    for(int i = 0; i < 32*1024;i++) {
        pool->schedule(createMyLoopTimeSubmit(),1);
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
    printf("---[ScheduledThreadPoolExecutor LoopSubmit case100] [OK]--- \n");
}
