#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ThreadCachedPoolExecutor.hpp"
#include "Integer.hpp"
#include "Executors.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "AutoLock.hpp"
#include "Mutex.hpp"
#include "ThreadCachedPoolExecutor.hpp"

using namespace obotcha;

Mutex cancelmutex = createMutex();
int cancelNum = 0;

DECLARE_SIMPLE_CLASS(CancelRunnable) IMPLEMENTS(Runnable) {
public:
   void run() {
      sleep(5);
   }

   void onInterrupt() {
     AutoLock l(cancelmutex);
     cancelNum++;
   }
};


int cancelTest() {
    while(1) {
        //printf("start test \n");
        ThreadCachedPoolExecutor pool = st(Executors)::newCachedThreadPool(1024*32,0,20,1000);
        ArrayList<Future> cancellists = createArrayList<Future>();
        //printf("start trace \n");
        for(int i = 0;i < 1024*32;i++) {
         //   printf("submit task num is %d \n",i);
            Future f = pool->submit(createCancelRunnable());
            cancellists->add(f);
        }

        for(int i = 0;i < 1024*32;i++) {
         //   printf("submit task num is %d \n",i);
            Future f = cancellists->get(i);
            f->cancel();
        }

        sleep(5);
        if(cancelNum != 1024*32) {
            printf("---[CacheThreadPool Test {cancel()} case1,cancelNum is %d] [FAIL]--- \n",cancelNum);
        }
        pool->shutdown();

        printf("---[CacheThreadPool Test {cancel()}case2] [OK]--- \n");
        break;
    }

    while(1) {
        //printf("start test \n");
        cancelNum = 0;
        ThreadCachedPoolExecutor pool = st(Executors)::newCachedThreadPool(1024*32,0,20,1000);
        ArrayList<Future> cancellists = createArrayList<Future>();
        //printf("start trace \n");
        for(int i = 0;i < 1024*32;i++) {
         //   printf("submit task num is %d \n",i);
            Future f = pool->submit(createCancelRunnable());
            cancellists->add(f);
        }
        pool->shutdown();
        sleep(5);

        if(cancelNum != 1024*32) {
            printf("---[CacheThreadPool Test {cancel()} case3,cancelNum is %d] [FAIL]--- \n",cancelNum);
        }
        printf("---[CacheThreadPool Test {cancel()}case4] [OK]--- \n");
        break;
    }
}
