#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "System.hpp"
#include "ThreadPoolExecutor.hpp"
#include "Error.hpp"

using namespace obotcha;

int count = 0;
DECLARE_CLASS(MySleepWaitRun) IMPLEMENTS(Runnable) {
public:
    void run() {
        try {
            st(Thread)::msleep();
        } catch(InterruptedException &e) {}
        count++;
    }
};

int testThreadQuickShutDown() {


    //TestThread onInterrupt case1
    while(1) {
        for(int i = 0;i < 32*1024;i++) {
            //printf("trace1 \n");
            ThreadPoolExecutor t = createThreadPoolExecutor(4,4);
            //printf("trace2 \n");
            t->submit(createMySleepWaitRun());
            t->submit(createMySleepWaitRun());
            t->submit(createMySleepWaitRun());
            t->submit(createMySleepWaitRun());
            //printf("trace3 \n");
            t->shutdown();
            //printf("trace4 \n");
            t->awaitTermination();
            //printf("trace5 \n");
        }

        printf("---[ThreadPoolExecutor Test {QuickShutDown()} special case1] [OK],count is %d--- \n",count);
        break;
    }


    return 0;

}
