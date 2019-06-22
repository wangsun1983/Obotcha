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

using namespace obotcha;

int num = 0;
Mutex mutex;


DECLARE_SIMPLE_CLASS(MyRunTest5) IMPLEMENTS(Runnable) {
public:
   void run() {
      AutoMutex l(mutex);
      num++;
      sleep(1);
   }
};


int numTest() {
    mutex = createMutex();
    ExecutorService pool = st(Executors)::newCachedThreadPool();
    while(1) {
        //start test 1
        int testNum = 64;
        int maxThreadNum = 0;
        for(int i = 0;i < testNum;i++) {
            MyRunTest5 run1 = createMyRunTest5();
            pool->execute(run1);

            int max = pool->getThreadsNum();
            if(pool->getThreadsNum() > maxThreadNum) {
            	maxThreadNum = max;
            }
        }

        sleep(64);

        if(num != testNum) {
            printf("---[TestCachedPoolExecutor NumTest {case1,num is %d] [FAIL]--- \n",num);
            break;
        }

        if(maxThreadNum != 32) {
            printf("---[TestCachedPoolExecutor NumTest {case2,maxThreadNum is %d] [FAIL]--- \n",maxThreadNum);
            break;
        }

        sleep(80);
        int threadsize = pool->getThreadsNum();
        if(threadsize != 0) {
            printf("---[TestCachedPoolExecutor NumTest {case3] [FAIL]--- \n");
            break;
        }

        printf("---[TestCachedPoolExecutor NumTest {case4] [Success]--- \n");
        break;
    }
}
