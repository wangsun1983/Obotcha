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
#include "Debug.hpp"
#include "ScheduledThreadPoolExecutor.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyReleaseTest) IMPLEMENTS(Runnable) {
public:
    _MyReleaseTest() {
        //printf("MyReleaseTest is %lx \n",this);
        incDebugReferenctCount();
    }

    void run() {
        //printf("MyReleaseTest running \n");
        sleep(5);
    }

    void onInterrupt() {
        //printf("MyReleaseTest interrupt \n");
    }

    ~_MyReleaseTest() {
        decDebugReferenctCount();
    }

    DEBUG_REFERENCE_DECLARATION
};

DEBUG_REFERENCE_REALIZATION(MyReleaseTest);



int ReleaseTest() {
    
    //_ScheduledThreadPoolExecutor() 
    while(1) {
        st(ScheduledThreadPoolExecutor)::initDebugReferenceCount();
        st(ScheduledThreadPoolThread)::initDebugReferenceCount();
        {
            ExecutorService pool = st(Executors)::newScheduledThreadPool();
            if(st(ScheduledThreadPoolExecutor)::getDebugReferenceCount() != 1
                ||st(ScheduledThreadPoolThread)::getDebugReferenceCount() != 1) {
                printf("---[ScheduledThreadPoolExecutor Test {Release} case1] [FAIL]--- \n");
                break;
            }
        }
        sleep(1);

        //printf("executor is %d \n",st(ScheduledThreadPoolExecutor)::getDebugReferenceCount());
        //printf("thread is %d \n",st(ScheduledThreadPoolThread)::getDebugReferenceCount());

        if(st(ScheduledThreadPoolExecutor)::getDebugReferenceCount() != 0
                ||st(ScheduledThreadPoolThread)::getDebugReferenceCount() != 0) {
            printf("---[ScheduledThreadPoolExecutor Test {Release} case2] [FAIL]--- \n");
            break;
        }

        printf("---[ScheduledThreadPoolExecutor Test {Release} case3] [Success]--- \n");
        break;
    }


    while(1) {
        st(ScheduledThreadPoolExecutor)::initDebugReferenceCount();
        st(ScheduledThreadPoolThread)::initDebugReferenceCount();
        st(MyReleaseTest)::initDebugReferenceCount();
        st(Thread)::initDebugReferenceCount();
        st(ScheduledTaskWorker)::initDebugReferenceCount();
        st(ScheduledThreadPoolTask)::initDebugReferenceCount();
        
        st(ThreadCachedPoolExecutorHandler)::initDebugReferenceCount();
        {
            ScheduledExecutorService pool = st(Executors)::newScheduledThreadPool();
            for(int i = 0; i < 50;i++) {
                pool->schedule(createMyReleaseTest(),100);
            }

            sleep(1);

            if(st(MyReleaseTest)::getDebugReferenceCount() != 50) {
                printf("---[ScheduledThreadPoolExecutor Test {Release} case4] [FAIL]--- \n");
                break;
            }
        }
        
        sleep(10);
        
        //printf("ScheduledThreadPoolExecutor is %d \n",st(ScheduledThreadPoolExecutor)::getDebugReferenceCount());
        //printf("ScheduledThreadPoolThread is %d \n",st(ScheduledThreadPoolThread)::getDebugReferenceCount());
        //printf("MyReleaseTest is %d \n",st(MyReleaseTest)::getDebugReferenceCount());
        //printf("Thread is %d \n",st(Thread)::getDebugReferenceCount());        
        //printf("ThreadCachedPoolExecutorHandler is %d \n",st(ThreadCachedPoolExecutorHandler)::getDebugReferenceCount());        
        //printf("ScheduledTaskWorker is %d \n",st(ScheduledTaskWorker)::getDebugReferenceCount());  
        //printf("ScheduledThreadPoolTask is %d \n",st(ScheduledThreadPoolTask)::getDebugReferenceCount());      
        
        if(st(ScheduledThreadPoolExecutor)::getDebugReferenceCount() != 0
             ||st(ScheduledThreadPoolThread)::getDebugReferenceCount() != 0
             ||st(MyReleaseTest)::getDebugReferenceCount() != 0
             ||st(Thread)::getDebugReferenceCount() != 0) {
            printf("---[ScheduledThreadPoolExecutor Test {Release} case5] [FAIL]--- \n");
            printf("ScheduledThreadPoolExecutor is %d \n",st(ScheduledThreadPoolExecutor)::getDebugReferenceCount());
        printf("ScheduledThreadPoolThread is %d \n",st(ScheduledThreadPoolThread)::getDebugReferenceCount());
        printf("MyReleaseTest is %d \n",st(MyReleaseTest)::getDebugReferenceCount());
        printf("Thread is %d \n",st(Thread)::getDebugReferenceCount());        
        printf("ThreadCachedPoolExecutorHandler is %d \n",st(ThreadCachedPoolExecutorHandler)::getDebugReferenceCount());        
        printf("ScheduledTaskWorker is %d \n",st(ScheduledTaskWorker)::getDebugReferenceCount());  
        printf("ScheduledThreadPoolTask is %d \n",st(ScheduledThreadPoolTask)::getDebugReferenceCount());
            break;
        }

        printf("---[ScheduledThreadPoolExecutor Test {Release} case6] [Success]--- \n");
        break;
    }


    while(1) {
        printf("start another test \n");

        st(ScheduledThreadPoolExecutor)::initDebugReferenceCount();
        st(ScheduledThreadPoolThread)::initDebugReferenceCount();
        st(MyReleaseTest)::initDebugReferenceCount();
        st(Thread)::initDebugReferenceCount();
        st(ScheduledTaskWorker)::initDebugReferenceCount();
        st(ScheduledThreadPoolTask)::initDebugReferenceCount();
        

        st(ThreadCachedPoolExecutorHandler)::initDebugReferenceCount();
        {
            printf("start another test1 \n");
        
            ScheduledExecutorService pool = st(Executors)::newScheduledThreadPool();
            for(int i = 0; i < 50;i++) {
                pool->schedule(createMyReleaseTest(),100);
            }

            sleep(3);
            if(st(MyReleaseTest)::getDebugReferenceCount() != 50) {
                printf("---[ScheduledThreadPoolExecutor Test {Release} case7] [FAIL]--- \n");
                break;
            }
            printf("start another test2 \n");
        
            pool->shutdown();
            printf("start another test3 \n");
        
            sleep(2);

            //printf("MyReleaseTest is %d \n",st(MyReleaseTest)::getDebugReferenceCount());
            //printf("Thread is %d \n",st(Thread)::getDebugReferenceCount());
            
            if(st(MyReleaseTest)::getDebugReferenceCount() != 0
             ||st(Thread)::getDebugReferenceCount() != 1) {//mTimeThread will be released when executor destroyed;
                printf("---[ScheduledThreadPoolExecutor Test {Release} case8] [FAIL]--- \n");
                break;
            }
            printf("start another test4 \n");
        
        }
        sleep(10);
        
        //printf("ScheduledThreadPoolExecutor is %d \n",st(ScheduledThreadPoolExecutor)::getDebugReferenceCount());
        //printf("ScheduledThreadPoolThread is %d \n",st(ScheduledThreadPoolThread)::getDebugReferenceCount());
        //printf("MyReleaseTest is %d \n",st(MyReleaseTest)::getDebugReferenceCount());
        //printf("Thread is %d \n",st(Thread)::getDebugReferenceCount());        
        //printf("ThreadCachedPoolExecutorHandler is %d \n",st(ThreadCachedPoolExecutorHandler)::getDebugReferenceCount());        
        //printf("ScheduledTaskWorker is %d \n",st(ScheduledTaskWorker)::getDebugReferenceCount());  
        //printf("ScheduledThreadPoolTask is %d \n",st(ScheduledThreadPoolTask)::getDebugReferenceCount());      
        
        if(st(ScheduledThreadPoolExecutor)::getDebugReferenceCount() != 0
             ||st(ScheduledThreadPoolThread)::getDebugReferenceCount() != 0
             ||st(Thread)::getDebugReferenceCount() != 0) {
            printf("---[ScheduledThreadPoolExecutor Test {Release} case9] [FAIL]--- \n");
            break;
        }

        printf("---[ScheduledThreadPoolExecutor Test {Release} case10] [Success]--- \n");
        break;
    }
}

