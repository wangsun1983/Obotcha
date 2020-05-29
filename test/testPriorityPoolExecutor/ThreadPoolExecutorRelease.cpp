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
#include "ThreadPriorityPoolExecutor.hpp"

using namespace obotcha;

Mutex numMutex = createMutex();
int releaseCount;

DECLARE_SIMPLE_CLASS(ReleaseunTest1) IMPLEMENTS(Runnable) {
public:
    _ReleaseunTest1() {
        //printf("create this is %lx \n",this);
    }

    void run() {
        sleep(1);
    }

    void onInterrupt() {
    }

    ~_ReleaseunTest1() {
        //decDebugReferenctCount();
        //printf("numMutex1 count is %d,this is %lx \n",numMutex->getStrongCount(),this);
        //{
        AutoLock ll(numMutex);
            //printf("numMutex2 count is %d \n",numMutex->getStrongCount());
        releaseCount++;
        //}
        //printf("numMutex2 count is %d,this is %lx \n",numMutex->getStrongCount(),this);

    }

};


int releaseTest() {
    while(1) {
        {
            ExecutorService pool = st(Executors)::newPriorityThreadPool();
            for(int i = 0;i<50;i++) {
                pool->submit(createReleaseunTest1());
            }

            pool->shutdown();
            sleep(10);
            if(pool->getThreadsNum() != 0) {
                printf("---[PriorityPoolExecutor Test {release()},thread num is %d case2] [FAIL]--- \n",pool->getThreadsNum());
                break;
            }

            if(releaseCount != 50) {
                printf("---[PriorityPoolExecutor Test {release()},count is %d case3] [FAIL]--- \n",releaseCount);
                break;
            }

            printf("---[PriorityPoolExecutor Test {release()}, case4] [Success]--- \n");
            break;
        }

        sleep(1);
        printf("---[PriorityPoolExecutor Test {release()} case5] [Success]--- \n");
        break;
    }

    sleep(1);

}
