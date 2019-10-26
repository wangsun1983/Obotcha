#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoMutex.hpp"
#include "System.hpp"
#include "ThreadPoolExecutor.hpp"
#include "Error.hpp"

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
    {
        ThreadPoolExecutor pool = createThreadPoolExecutor();
        pool->submit(createMyDestroyTest());
        pool->shutdown();
    }
    sleep(10);
    return 0;

}
