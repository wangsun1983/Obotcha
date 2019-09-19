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
#include "ThreadPoolExecutor.hpp"

using namespace obotcha;

Mutex numMutex = createMutex();
int releaseCount;

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

int releaseTest() {
    while(1) {
        {
            st(ThreadPoolExecutor)::initDebugReferenceCount();
            st(ThreadPoolExecutorHandler)::initDebugReferenceCount();
            st(Thread)::initDebugReferenceCount();
            st(ReleaseunTest1)::initDebugReferenceCount();

            ExecutorService pool = st(Executors)::newFixedThreadPool(50,8);
            for(int i = 0;i<50;i++) {
                pool->submit(createReleaseunTest1());
            }

            //printf("1ThreadPoolExecutor getDebugReferenceCount is %d \n",st(ThreadPoolExecutor)::getDebugReferenceCount());
            //printf("1ThreadPoolExecutorHandler getDebugReferenceCount is %d \n",st(ThreadPoolExecutorHandler)::getDebugReferenceCount());
            //printf("1Thread getDebugReferenceCount is %d \n",st(ThreadPoolExecutorHandler)::getDebugReferenceCount());
            //printf("1ReleaseunTest1 is %d \n",st(ReleaseunTest1)::getDebugReferenceCount());

            if(st(ReleaseunTest1)::getDebugReferenceCount() != 50
                ||st(ThreadPoolExecutor)::getDebugReferenceCount() != 1
                ||st(ThreadPoolExecutorHandler)::getDebugReferenceCount() != 8
                ||st(Thread)::getDebugReferenceCount() != 8 ) {
                printf("---[TestThreadPoolExecutor Test {release()}case1] [FAIL]--- \n");
                break;
            }

            pool->shutdown();
            sleep(10);
            if(pool->getThreadsNum() != 0) {
                printf("---[TestThreadPoolExecutor Test {release()},thread num is %d case2] [FAIL]--- \n",pool->getThreadsNum());
                break;
            }

            if(releaseCount != 50) {
                printf("---[TestThreadPoolExecutor Test {release()},count is %d case3] [FAIL]--- \n",releaseCount);
                break;
            }

            printf("---[TestThreadPoolExecutor Test {release()}, case4] [Success]--- \n");
            break;
        }

        sleep(1);
        if(st(ThreadPoolExecutor)::getDebugReferenceCount() != 0 
            || st(ThreadPoolExecutorHandler)::getDebugReferenceCount() != 0
            || st(Thread)::getDebugReferenceCount() != 0
            || st(ReleaseunTest1)::getDebugReferenceCount() != 0) {
            
            printf("---[TestThreadPoolExecutor Test {release()}, case4] [FAIL]--- \n");
            break;
        }

        printf("---[TestThreadPoolExecutor Test {release()} case5] [Success]--- \n");
        break;
    }

    sleep(1);

}

