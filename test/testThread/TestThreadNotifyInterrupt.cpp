#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "System.hpp"
#include "Condition.hpp"

#define TEST_DEVIATION 50 //ms
#define TEST_SLEEP_INTERVAL 100 //s

static int disposeVal = -1;

using namespace obotcha;

Mutex myNotifyMutex = createMutex();
Condition mCondition = createCondition();
int notifyint = 1;

DECLARE_SIMPLE_CLASS(MyNotifyTest1Thread) IMPLEMENTS(Thread) {
public:
    void run() {
        //printf("notify run1 \n");
        AutoLock ll(myNotifyMutex);
        //printf("notify run2 \n");
        mCondition->wait(myNotifyMutex);
        //printf("notify run3 \n");
    }

    ~_MyNotifyTest1Thread() {

    }

    void onInterrupt() {
        //printf("i notify!!!!! onInterrupt \n");
        notifyint = 2;
    }
};

int testThreadNotifyInterruptCase() {
    //TestThread onInterrupt case1
    while(1) {
        MyNotifyTest1Thread thread = createMyNotifyTest1Thread();
        thread->start();
        sleep(1);
        //thread->quit();
        sleep(1);
        if(notifyint != 2) {
            printf("---[Thread Test {Interrupt()} special case1] [FAILED]--- \n");
            break;
        }

        printf("---[Thread Test {Interrupt()} special case2] [OK]--- \n");
        break;
    }

}
