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

DECLARE_CLASS(MyDestroyTest) IMPLEMENTS(Runnable) {
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
    while(1) {
        //try {
            {
                ThreadPoolExecutor pool = createExecutorBuilder()->newThreadPool();
                pool->submit(createMyDestroyTest());
                pool->shutdown();
            }
            sleep(10);
        //} catch(ExecutorDestructorException e) {
        //    printf("---[ThreadPoolExecutor Test {destroy()} special case1] [FAIL]--- \n");
        //    break;
        //}

        printf("---[ThreadPoolExecutor Test {destroy()} special case1] [OK]--- \n");
        break;
    }

    return 0;

}
