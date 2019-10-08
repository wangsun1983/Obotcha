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

Mutex numMutex = createMutex();
int releaseCount = 0;

DECLARE_SIMPLE_CLASS(ReleaseunTest1) IMPLEMENTS(Runnable) {
public:
    _ReleaseunTest1() {
        //printf("create this is %lx \n",this);
        incDebugReferenctCount();
    }

    void run() {
        sleep(1);
    }

    void onInterrupt() {
    }

    ~_ReleaseunTest1() {
        decDebugReferenctCount();
        //printf("numMutex1 count is %d,this is %lx \n",numMutex->getStrongCount(),this);
        //{
        AutoMutex ll(numMutex);
            //printf("numMutex2 count is %d \n",numMutex->getStrongCount());
        releaseCount++;    
        //}
        //printf("numMutex2 count is %d,this is %lx \n",numMutex->getStrongCount(),this);
        
    }

    DEBUG_REFERENCE_DECLARATION
};

DEBUG_REFERENCE_REALIZATION(ReleaseunTest1);


int priorityPoolReleaseTest() {
    
    //_ThreadPoolExecutor(int queuesize,int threadnum);
    while(1) {
        st(PriorityPoolThread)::initDebugReferenceCount();
        st(PriorityPoolExecutor)::initDebugReferenceCount();
        st(Thread)::initDebugReferenceCount();
        {
            ExecutorService pool = st(Executors)::newPriorityThreadPool();

            if(st(PriorityPoolExecutor)::getDebugReferenceCount() == 0
                ||st(PriorityPoolThread)::getDebugReferenceCount() == 0
                ||st(Thread)::getDebugReferenceCount() == 0) {

                printf("---[PriorityThreadPoolExecutor Test {release()} case1] [FAIL]--- \n");
                break;
            }
        }

        sleep(1);
        if(st(PriorityPoolExecutor)::getDebugReferenceCount() != 0
                ||st(PriorityPoolThread)::getDebugReferenceCount() != 0
                ||st(Thread)::getDebugReferenceCount() != 0) {

            printf("---[PriorityThreadPoolExecutor Test {release()} case2] [FAIL]--- \n");
            break;
        }

        printf("---[PriorityThreadPoolExecutor Test {release()} case3] [Success]--- \n");
        break;
    }
    sleep(1);

    while(1) {
        st(PriorityPoolThread)::initDebugReferenceCount();
        st(PriorityPoolExecutor)::initDebugReferenceCount();
        st(Thread)::initDebugReferenceCount();
        st(ReleaseunTest1)::initDebugReferenceCount();
        {
            ExecutorService pool = st(Executors)::newPriorityThreadPool();
            for(int i = 0;i<10;i++) {
                pool->submit(TaskPriorityMedium,createReleaseunTest1());
            }

            //printf("ReleaseunTest1::getDebugReferenceCount is %d \n",st(ReleaseunTest1)::getDebugReferenceCount());

            if(st(ReleaseunTest1)::getDebugReferenceCount() == 0) {
                printf("---[PriorityThreadPoolExecutor Test {release()} case4] [FAIL]--- \n");
                break;
            }

            sleep(10);
            if(st(ReleaseunTest1)::getDebugReferenceCount() != 0
                ||st(PriorityPoolThread)::getDebugReferenceCount() != st(System)::availableProcessors()) {
                printf("---[PriorityThreadPoolExecutor Test {release()} case5] [FAIL]--- \n");
                break;
            }
        }

        sleep(1);

        if(st(PriorityPoolExecutor)::getDebugReferenceCount() != 0) {
            printf("---[PriorityThreadPoolExecutor Test {release()} case6] [FAIL]--- \n");
            break;
        }

        printf("---[PriorityThreadPoolExecutor Test {release()} case7] [Success]--- \n");
        break;
    }
}

