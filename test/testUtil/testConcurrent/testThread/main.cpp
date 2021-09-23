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

extern void testThreadInterruptCase();
extern void testThreadCommonCase();
//extern void testThreadNotifyInterruptCase();
extern void testThreadSleepInterrupt();
//extern void testThreadLoopInterrypt();
extern void testThreadRelease();
extern void testThreadJoin();
extern void testThreadStart();
//extern void testThreadClose();
extern void testThreadLoopCreate();
extern void testThreadLoopJoin();
//extern void testthreadloopquit();
extern void testThreadLambda();
extern void testThreadjoinCase2();
extern void testThreadSleep();
extern void testThreadQuickJoin();
extern void testThreadSleepRelease();
extern void testThreadPriority();
extern void testThreadInterruptCase();
extern void testThreadLoopStart();
extern void testThreadInterruptSleep();

int main() {
    testThreadInterruptSleep();
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
