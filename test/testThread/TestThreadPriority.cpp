#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "System.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyPriorityThread) EXTENDS(Thread) {
public:
    void run() {
        setPriority(st(Thread)::ThreadPriority::High);
        int priority = getPriority();
        if(priority != st(Thread)::ThreadPriority::High) {
            printf("---[Thread Test {Set Priority()} case1][FAILED]---,priority is %d \n",priority);
        }

        sleep(100);
        setPriority(st(Thread)::ThreadPriority::Low);
        priority = getPriority();
        if(priority != st(Thread)::ThreadPriority::Low) {
            printf("---[Thread Test {Set Priority()} case2][FAILED]---,priority is %d \n",priority);
        }

        sleep(100);
        setPriority(st(Thread)::ThreadPriority::Normal);
        priority = getPriority();
        if(priority != st(Thread)::ThreadPriority::Normal) {
            printf("---[Thread Test {Set Priority()} case3][FAILED]---,priority is %d \n",priority);
        }

        sleep(100);
        setPriority(st(Thread)::ThreadPriority::Highest);
        priority = getPriority();
        if(priority != st(Thread)::ThreadPriority::Highest) {
            printf("---[Thread Test {Set Priority()} case4][FAILED]---,priority is %d \n",priority);
        }

        sleep(100);
        setPriority(st(Thread)::ThreadPriority::Realtime);
        priority = getPriority();
        if(priority != st(Thread)::ThreadPriority::Realtime) {
            printf("---[Thread Test {Set Priority()} case5][FAILED]---,priority is %d \n",priority);
        }

        printf("---[Thread Test {Set Priority()} case6][OK]---\n");
    }
};


int testThreadPriority() {
    //TestThread onInterrupt case1
    MyPriorityThread t = createMyPriorityThread();
    t->start();
    t->join();

}
