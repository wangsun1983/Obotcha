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

using namespace obotcha;

int interruptVal = 1;

DECLARE_SIMPLE_CLASS(RunTest1) IMPLEMENTS(Runnable) {
public:
    void run() {
        printf("i am running \n");
        sleep(10);
    }

    void onInterrupt() {
        printf("i am interrupt \n");
        interruptVal = 2;
    }

    ~_RunTest1() {
        //printf("i am release \n");
        //unDestory = 0;
    }
};



int testRunnable_onInterrupt() {
    printf("---[TestThreadPoolExecutor Test Start]--- \n");

    //void shutdown();
    while(1) {
        ExecutorService pool = st(Executors)::newFixedThreadPool(100,100);
        pool->submit(createRunTest1());
        printf("start shudown now \n");
        pool->shutdownNow();
        printf("start shudown now 1\n");
        sleep(5);
        if(interruptVal != 2) {
            printf("---[TestThreadPoolExecutor TestOnInterrupt {onInterrupt()} case1] [FAIL]--- \n");
            break;
        }

        printf("---[TestThreadPoolExecutor TestOnInterrupt {onInterrupt()} case1] [Success]--- \n");
        break;
    }

}

