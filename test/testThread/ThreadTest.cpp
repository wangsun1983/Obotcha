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

int main() {

    //testthreadloopquit(); //no use
    //testThreadNotifyInterruptCase(); no use   
    //testThreadLoopInterrypt(); no use
    //testThreadClose(); no use

#if 0
    testThreadStart();
    testThreadJoin();
    testThreadInterruptCase();
    testThreadCommonCase();
    testThreadSleepInterrupt();
    testThreadRelease();
    testThreadLoopCreate();
    testThreadLoopJoin();
#endif    
    testThreadLambda();
    sleep(10);
}
