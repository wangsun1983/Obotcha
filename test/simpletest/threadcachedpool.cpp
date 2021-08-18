#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ThreadCachedPoolExecutor.hpp"
#include "ThreadPriorityPoolExecutor.hpp"
#include "AutoLock.hpp"

using namespace obotcha;

int runDestory = 1;
DECLARE_CLASS(RunTest1) IMPLEMENTS(Runnable) {
public:
    void run() {
        printf("run test1 start 1\n");
        try {
            st(Thread)::sleep(1*1000);
        } catch(InterruptedException &e){
            printf("run test1 start 1_1 \n");
        }
        printf("run test1 start 2\n");
    }

    void onInterrupt() {
    }

    ~_RunTest1() {
        runDestory = 0;
    }
};

Condition c = createCondition();
Mutex m = createMutex();

DECLARE_CLASS(RunTest2) IMPLEMENTS(Runnable) {
public:
    _RunTest2() {
        //c = createCondition();
        //m = createMutex();
    }

    void run() {        
        printf("run test2 start 1\n");
        try {
            AutoLock l(m);
            c->wait(m);
        } catch(InterruptedException &e){
            printf("run test2 start 1_1 \n");
        }
        printf("run test2 start 2\n");
    }

    void onInterrupt() {
    }

    ~_RunTest2() {
        runDestory = 0;
    }
private:
    //Condition c;
    //Mutex m;
};

int main() {
    
    //ThreadCachedPoolExecutor t = createThreadCachedPoolExecutor();
#if 0
    ThreadPriorityPoolExecutor t = createThreadPriorityPoolExecutor();
    int vv1 = 21;
    t->submit(st(ThreadPriorityPoolExecutor)::PriorityMedium,createRunTest1());
    //sleep(1);
    //t->shutdown();
    sleep(20);

    printf("thread num is %d \n",t->getThreadsNum());
#endif

    Thread t = createThread(createRunTest2());
    t->start();
    sleep(1);
    t->interrupt();
    sleep(10);

    return 0;
}