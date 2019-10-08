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
#include "PriorityPoolExecutor.hpp"
#include "System.hpp"

using namespace obotcha;

Mutex interruptMutex = createMutex();
int interruptCount = 0;

DECLARE_SIMPLE_CLASS(InterruptTest1) IMPLEMENTS(Runnable) {
public:
    _InterruptTest1() {
        //printf("create this is %lx \n",this);
        //incDebugReferenctCount();
    }

    void run() {
        //printf("run this is %lx \n",this);
        while(1) {
            sleep(1);    
        }
    }

    void onInterrupt() {
        //printf("onInterrupt this is %lx \n",this);
        AutoMutex ll(interruptMutex);
        interruptCount++;
    }

    ~_InterruptTest1() {
    }

};


int priorityPoolInterruptTest() {
    
    //case 1
    
    while(1) {
        ExecutorService pool = st(Executors)::newPriorityThreadPool();
        for(int i = 0;i<100;i++) {
            pool->submit(TaskPriorityMedium,createInterruptTest1());    
        }
        
        pool->shutdown();
        
        sleep(1);
        
        if(interruptCount != 100) {
            printf("---[PriorityThreadPoolExecutor Test {interrupt()} case1] [FAIL]--- \n");
            break;
        }

        printf("---[PriorityThreadPoolExecutor Test {interrupt()} case2] [Success]--- \n");
        break;
    }

}

