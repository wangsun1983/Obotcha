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
#include "AutoLock.hpp"
#include "Mutex.hpp"
#include "ThreadCachedPoolExecutor.hpp"
#include "AtomicInteger.hpp"
#include "ArrayList.hpp"

using namespace obotcha;

//AtomicInteger submitLoopValue1 = createAtomicInteger(0);
Mutex ttt = createMutex();
int vv = 0;
ArrayList<int> checksubmitList = createArrayList<int>(100001);

DECLARE_SIMPLE_CLASS(SubmitLoopRun1) IMPLEMENTS(Runnable) {
public:
   void run() {
      ttt->lock();
      //submitLoopValue1->incrementAndGet();
      //printf("vv is %d \n");
      checksubmitList->set(vv,1);
      vv++;
      ttt->unlock();
   }
};


int loopsubmittest() {
    while(1) {
        printf("checksubmitList size is %d\n",checksubmitList->size());
        for(int i = 0; i < 100000;i++) {
          checksubmitList->set(i,0);
        }

        ExecutorService pool = st(Executors)::newCachedThreadPool(100,0,20,1000);
        printf("start trace \n");
        for(int i = 0;i < 100000;i++) {
            pool->submit(createSubmitLoopRun1());
        }

        sleep(10);
        pool->shutdown();

        for(int i = 0; i < 100000;i++) {
          if(checksubmitList->get(i) != 1) {
            printf("value is %d,index is %d \n",checksubmitList->get(i),i);
          }
        }

        if(vv != 100000) {
          printf("---[CacheThreadPool loopsumit case1],value is %d [FAIL]--- \n",vv);
        }

        printf("---[CacheThreadPool loopsumit case100] [OK]--- \n");

        break;
    }
}
