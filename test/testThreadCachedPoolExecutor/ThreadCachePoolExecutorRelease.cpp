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
};


int releaseTest() {
    while(1) {
        //printf("start test \n");
        ExecutorService pool = st(Executors)::newCachedThreadPool(100,0,20,1000);
        //printf("start trace \n");
        for(int i = 0;i < 100;i++) {
         //   printf("submit task num is %d \n",i);
            pool->submit(createReleaseTestRunnable());
        }
        //printf("handler count1 is %d \n",st(ThreadCachedPoolExecutorHandler)::getDebugReferenceCount());

        sleep(200);
        pool->shutdown();
        printf("---[CacheThreadPool Test {release()}case4] [Success]--- \n");
        break;
    }
}
