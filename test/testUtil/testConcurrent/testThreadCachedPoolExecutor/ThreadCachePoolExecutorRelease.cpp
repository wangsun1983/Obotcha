#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ThreadCachedPoolExecutor.hpp"
#include "Integer.hpp"
#include "ExecutorBuilder.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "AutoLock.hpp"
#include "Mutex.hpp"
#include "ThreadCachedPoolExecutor.hpp"

using namespace obotcha;

DECLARE_CLASS(ReleaseTestRunnable) IMPLEMENTS(Runnable) {
public:
   void run() {
      sleep(1);
   }
};

int releaseTest() {
    while(1) {
        //ThreadCachedPoolExecutor pool = st(Executors)::newCachedThreadPool(100,0,20,1000);
        ThreadCachedPoolExecutor pool = createExecutorBuilder()
                                        ->setQueueSize(100)
                                        ->setMinThreadNum(0)
                                        ->setMaxThreadNum(20)
                                        ->setTimeout(1000)
                                        ->newCachedThreadPool();
        for(int i = 0;i < 100;i++) {
            pool->submit(createReleaseTestRunnable());
        }
        sleep(200);
        pool->shutdown();
        printf("---[CacheThreadPool Test {release()}case4] [Success]--- \n");
        break;
    }
}
