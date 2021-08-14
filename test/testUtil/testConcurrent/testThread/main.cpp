#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "System.hpp"

#define TEST_DEVIATION 50 //ms
#define TEST_SLEEP_INTERVAL 100 //s

static int disposeVal = -1;

using namespace obotcha;

extern int testThreadInterruptCase();
extern int testThreadCommonCase();
//extern int testThreadNotifyInterruptCase();
extern int testThreadSleepInterrupt();
//extern int testThreadLoopInterrypt();
extern int testThreadRelease();
extern int testThreadJoin();
extern int testThreadStart();
//extern int testThreadClose();
extern int testThreadLoopCreate();
extern int testThreadLoopJoin();
//extern int testthreadloopquit();
extern int testThreadLambda();
extern int testThreadjoinCase2();
extern int testThreadSleep();
extern int testThreadQuickJoin();
extern int testThreadSleepRelease();
extern int testThreadPriority();
extern int testThreadInterruptCase();
extern int testThreadLoopStart();

int main() {
    testThreadStart();
    testThreadInterruptCase();
    testThreadJoin();
    testThreadInterruptCase();
    testThreadCommonCase();
    testThreadSleepInterrupt();
    testThreadRelease();
    testThreadLoopCreate();
    testThreadLoopJoin();
    testThreadLambda();
    testThreadjoinCase2();
    testThreadSleep();
    testThreadQuickJoin();
    testThreadSleepRelease();
    testThreadPriority();
    testThreadLoopStart();
    sleep(10);
    return 0;
}
