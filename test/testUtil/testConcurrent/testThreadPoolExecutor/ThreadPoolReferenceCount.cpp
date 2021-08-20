#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "System.hpp"
#include "ExecutorBuilder.hpp"
#include "Error.hpp"

using namespace obotcha;

int testPoolReferenceCount() {

    while(1) {
        ThreadPoolExecutor pool = nullptr;
        {
            pool = createExecutorBuilder()->setThreadNum(4)->newThreadPool();
            pool->submit([]() {
              try {
                st(Thread)::interruptableSleep(10);
              } catch(InterruptedException &e){}
            });

            pool->submit([]() {
              try {
                st(Thread)::interruptableSleep(10);
              } catch(InterruptedException &e){}
            });

            pool->submit([]() {
              try {
                st(Thread)::interruptableSleep(10);
              } catch(InterruptedException &e){}
            });
        }

        if(pool->getStrongCount() != 9) {
          printf("---[ThreadPoolExecutor Test Reference count is %d case1] [FAIL]--- \n",pool->getStrongCount());
          //break;
        }

        pool->shutdown();
        sleep(11);
        if(pool->getStrongCount() != 1) {
          printf("---[ThreadPoolExecutor Test Reference count is %d case2] [FAIL]--- \n",pool->getStrongCount());
          //break;
        }
        sleep(5);
        if(pool->getStrongCount() != 1) {
          printf("---[ThreadPoolExecutor Test Reference count is %d case3] [FAIL]--- \n",pool->getStrongCount());
          //break;
        }

        printf("---[ThreadPoolExecutor Test Reference case4] [OK]--- \n");
        break;
    }

    return 0;

}
