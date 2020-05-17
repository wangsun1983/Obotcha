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

using namespace obotcha;

AtomicInteger myloopvalue = createAtomicInteger(0);

DECLARE_SIMPLE_CLASS(MyLoopSubmit) IMPLEMENTS(Runnable) {
public:

    void run() {
        myloopvalue->incrementAndGet();
    }

    void onInterrupt() {
        printf("MyLoopSubmit interrupt \n");
    }
};


int scheduleloopsubmit() {
    //test1
    ScheduledExecutorService pool = st(Executors)::newScheduledThreadPool();
    for(int i = 0; i < 32*1024;i++) {
        pool->schedule(createMyReleaseTest(),0);
    }

    sleep(1);
    if(myloopvalue->get() != 32*1024) {
        printf("---[ScheduledThreadPoolExecutor LoopSubmit case1],value is %d [FAIL]--- \n",myloopvalue->get());
    }
    pool->shutdown();

    //test2
    myloopvalue = createAtomicInteger(0);
    pool = st(Executors)::newScheduledThreadPool();
    for(int i = 0; i < 32*1024;i++) {
        pool->schedule(createMyReleaseTest(),100);
    }

    if(myloopvalue->get() != 32*1024) {
        printf("---[ScheduledThreadPoolExecutor LoopSubmit case2],value is %d [FAIL]--- \n",myloopvalue->get());
    }
    pool->shutdown();

    printf("---[ScheduledThreadPoolExecutor LoopSubmit case100] [Success]--- \n");
}
