#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Integer.hpp"
#include "ExecutorBuilder.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "InterruptedException.hpp"

using namespace obotcha;

int interruptVal = 1;

DECLARE_SIMPLE_CLASS(RunTest1) IMPLEMENTS(Runnable) {
public:
    void run() {
        //printf("i am running \n");
        try {
            st(Thread)::msleep(10*1000);
        } catch(InterruptedException &e) {
            interruptVal = 2;
        }

    }

    ~_RunTest1() {
        //printf("i am release \n");
        //unDestory = 0;
        //interruptVal = 1;
    }
};



int testRunnable_onInterrupt() {
    printf("---[TestThreadPoolExecutor Test Start]--- \n");

    //void shutdown();
    while(1) {
        ThreadPoolExecutor pool = createExecutorBuilder()->setQueueSize(100)->setThreadNum(100)->newThreadPool();
        pool->submit(createRunTest1());
        sleep(1);
        pool->shutdown();
        sleep(5);
        if(interruptVal != 2) {
            printf("---[TestThreadPoolExecutor TestOnInterrupt {onInterrupt(),interruptVal is %d} case1] [FAIL]--- \n",interruptVal);
            break;
        }

        printf("---[TestThreadPoolExecutor TestOnInterrupt {onInterrupt()} case1] [OK]--- \n");
        break;
    }

}
