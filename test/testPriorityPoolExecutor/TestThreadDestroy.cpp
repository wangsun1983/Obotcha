#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "System.hpp"
#include "ThreadPriorityPoolExecutor.hpp"
#include "ExecutorDestructorException.hpp"
#include "Error.hpp"
#include "Executors.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyDestroyTest) IMPLEMENTS(Runnable) {
public:
    void run() {
        //printf("i am running123 \n");
        sleep(5);
    }

    void onInterrupt() {
    }
};

int testThreadDestroy() {

    //TestThread onInterrupt case1
#if 0
    while(1)
    {
        try {
            {
                ExecutorService pool = st(Executors)::newPriorityThreadPool();
                pool->submit(createMyDestroyTest());
                pool->shutdown();
            }
            sleep(10);
        } catch(ExecutorDestructorException e) {
            printf("---[PriorityPoolExecutor Test {destroy()} special case1] [Success]--- \n");
            break;
        }

        printf("---[PriorityPoolExecutor Test {destroy()} special case1] [Fail]--- \n");
        break;
    }
#endif
    return 0;

}
