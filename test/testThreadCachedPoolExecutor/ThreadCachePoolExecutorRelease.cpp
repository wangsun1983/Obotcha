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
#include "AutoMutex.hpp"
#include "Mutex.hpp"
#include "ThreadCachedPoolExecutor.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(ReleaseTestRunnable) IMPLEMENTS(Runnable) {
public:
   void run() {
      //while(1) {
          //printf("myruntest 5 trace2 \n");
          sleep(1);
          //printf("myruntest 5 trace3 \n");
      //}
   }

   DEBUG_REFERENCE_DECLARATION
};

DEBUG_REFERENCE_REALIZATION(ReleaseTestRunnable);

int releaseTest() {
    while(1) {
        st(ThreadCachedPoolExecutorHandler)::initDebugReferenceCount();
        st(ThreadCachedPoolExecutor)::initDebugReferenceCount();
        st(Thread)::initDebugReferenceCount();
        st(ReleaseTestRunnable)::initDebugReferenceCount();
        //printf("start test \n");
        ExecutorService pool = st(Executors)::newCachedThreadPool(100,0,20,1000);
        //printf("start trace \n");
        for(int i = 0;i < 100;i++) {
         //   printf("submit task num is %d \n",i);
            pool->submit(createReleaseTestRunnable());  
        }
        //printf("handler count1 is %d \n",st(ThreadCachedPoolExecutorHandler)::getDebugReferenceCount());

        sleep(200);
        
        //printf("handler count2 is %d \n",st(ThreadCachedPoolExecutorHandler)::getDebugReferenceCount());
        if(st(ThreadCachedPoolExecutorHandler)::getDebugReferenceCount() != 0) {
            printf("---[CacheThreadPool Test {release()}case1] [FAIL]--- \n");
            break;
        }

        if(st(ReleaseTestRunnable)::getDebugReferenceCount() != 0) {
            printf("---[CacheThreadPool Test {release()}case2] [FAIL]--- \n");
            break;
        }

        if(st(Thread)::getDebugReferenceCount() != 0) {
            printf("---[CacheThreadPool Test {release()}case3] [FAIL]--- \n");
            break;
        }

        printf("---[CacheThreadPool Test {release()}case4] [Success]--- \n");
        break;
    }
}
