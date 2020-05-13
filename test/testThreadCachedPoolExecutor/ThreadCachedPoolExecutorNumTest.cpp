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

using namespace obotcha;

int num = 0;
Mutex mutex;

DECLARE_SIMPLE_CLASS(MyRunTest5) IMPLEMENTS(Runnable) {
public:
   void run() {
      //printf("myruntest 5 trace1 \n");
      {
          AutoLock l(mutex);
          num++;
      }
      //printf("myruntest 5 trace2 \n");
      //sleep(1);
      //printf("myruntest 5 trace3 \n");
   }
};


int numTest() {
    mutex = createMutex();
    ExecutorService pool = st(Executors)::newCachedThreadPool();
    while(1) {
        //start test 1
        int testNum = 1024*32;
        //int maxThreadNum = 0;
        for(int i = 0;i < testNum;i++) {
            MyRunTest5 run1 = createMyRunTest5();
            pool->execute(run1);
        }

        int maxThreadNum = pool->getThreadsNum();
        printf("maxtread is %d \n",maxThreadNum);

        sleep(20);

        if(num != testNum) {
            printf("---[TestCachedPoolExecutor NumTest {case1,num is %d] [FAIL]--- \n",num);
            pool->shutdown();
            break;
        }

        if(maxThreadNum != 4) {
            pool->shutdown();
            printf("---[TestCachedPoolExecutor NumTest {case2,maxThreadNum is %d] [FAIL]--- \n",maxThreadNum);
            break;
        }

        sleep(80);
        int threadsize = pool->getThreadsNum();
        if(threadsize != 0) {
            pool->shutdown();
            printf("---[TestCachedPoolExecutor NumTest {case3] [FAIL]---,thread size is  %d \n",threadsize);
            break;
        }

        pool->shutdown();
        printf("---[TestCachedPoolExecutor NumTest {case4] [Success]--- \n");
        break;
    }
}
