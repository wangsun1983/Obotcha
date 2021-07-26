#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "System.hpp"
#include "Error.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyPriorityThread) EXTENDS(Thread) {
public:
    void run() {
        setPriority(st(Thread)::ThreadPriority::High);
        int priority = getPriority();
        if(priority != -NotSupport) {
            printf("---[Thread Test {Set Priority()} case1][FAILED]---,priority is %d \n",priority);
        }

        sleep(100);
        setPriority(st(Thread)::ThreadPriority::Low);
        priority = getPriority();
        if(priority != -NotSupport) {
            printf("---[Thread Test {Set Priority()} case2][FAILED]---,priority is %d \n",priority);
        }

        sleep(100);
        setPriority(st(Thread)::ThreadPriority::Normal);
        priority = getPriority();
        if(priority != -NotSupport) {
            printf("---[Thread Test {Set Priority()} case3][FAILED]---,priority is %d \n",priority);
        }

        sleep(100);
        setPriority(st(Thread)::ThreadPriority::Highest);
        priority = getPriority();
        if(priority != -NotSupport) {
            printf("---[Thread Test {Set Priority()} case4][FAILED]---,priority is %d \n",priority);
        }

        sleep(100);
        setPriority(st(Thread)::ThreadPriority::Realtime);
        priority = getPriority();
        if(priority != -NotSupport) {
            printf("---[Thread Test {Set Priority()} case5][FAILED]---,priority is %d \n",priority);
        }

        /////////////////////////////////policy changed
        setSchedPolicy(st(Thread)::SchedType::Fifo);
        int policy = getSchedPolicy();
        if(policy != st(Thread)::SchedType::Fifo) {
            printf("---[Thread Test {Set Priority()} case6][FAILED]---,policy is %d \n",policy);
        }
        
        int ret = setPriority(st(Thread)::ThreadPriority::Low);
        priority = getPriority();
        if(priority != st(Thread)::ThreadPriority::Low) {
            printf("---[Thread Test {Set Priority()} case7][FAILED]---,priority is %d,ret is %d \n",priority,ret);
        }

        sleep(100);
        setPriority(st(Thread)::ThreadPriority::Normal);
        priority = getPriority();
        if(priority != st(Thread)::ThreadPriority::Normal) {
            printf("---[Thread Test {Set Priority()} case8][FAILED]---,priority is %d \n",priority);
        }

        sleep(100);
        setPriority(st(Thread)::ThreadPriority::Highest);
        priority = getPriority();
        if(priority != st(Thread)::ThreadPriority::Highest) {
            printf("---[Thread Test {Set Priority()} case9][FAILED]---,priority is %d \n",priority);
        }

        sleep(100);
        setPriority(st(Thread)::ThreadPriority::Realtime);
        priority = getPriority();
        if(priority != st(Thread)::ThreadPriority::Realtime) {
            printf("---[Thread Test {Set Priority()} case10][FAILED]---,priority is %d \n",priority);
        }




        printf("---[Thread Test {Set Priority()} case20][OK]---\n");
    }
};


int testThreadPriority() {
    //TestThread onInterrupt case1
    MyPriorityThread t = createMyPriorityThread();
    t->start();
    t->join();

}
