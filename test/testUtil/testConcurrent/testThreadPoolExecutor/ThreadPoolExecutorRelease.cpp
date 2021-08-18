#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ThreadPoolExecutor.hpp"
#include "Integer.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "ThreadPoolExecutor.hpp"
#include "ExecutorBuilder.hpp"

using namespace obotcha;

Mutex numMutex = createMutex();
int releaseCount;

DECLARE_CLASS(ReleaseunTest1) IMPLEMENTS(Runnable) {
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
            ThreadPoolExecutor pool = createExecutorBuilder()->setQueueSize(50)->setThreadNum(8)->newThreadPool();//st(Executors)::newFixedThreadPool(50,8);
            for(int i = 0;i<50;i++) {
                pool->submit(createReleaseunTest1());
            }

            pool->shutdown();
            sleep(10);
            if(pool->getThreadsNum() != 8) {
                printf("---[TestThreadPoolExecutor Test {release()},thread num is %d case2] [FAIL]--- \n",pool->getThreadsNum());
                break;
            }

            if(releaseCount != 50) {
                printf("---[TestThreadPoolExecutor Test {release()},count is %d case3] [FAIL]--- \n",releaseCount);
                break;
            }

            printf("---[TestThreadPoolExecutor Test {release()}, case4] [OK]--- \n");
            break;
        }

        sleep(1);
        printf("---[TestThreadPoolExecutor Test {release()} case5] [OK]--- \n");
        break;
    }

    sleep(1);

}
