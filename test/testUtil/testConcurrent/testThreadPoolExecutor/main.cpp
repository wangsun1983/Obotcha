#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Integer.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"

using namespace obotcha;

extern int normalTest();
extern int testRunnable_onInterrupt();
extern int releaseTest();
extern int testThreadShutdown();
extern int testThreadDestroy();
extern int testThreadPoolLoopSubmit();
extern int testThreadPoolLoopShutdown();
extern int testThreadLambda();
extern int testThreadQuickShutDown();
extern int testPoolReferenceCount();
extern void testThreadPoolSubmit_Wait();
extern void testThreadPoolSubmit_ShutDown();
extern void testThreadLambdaSubmitTimeout();
extern void testThreadLambdaExecuteTimeout();
extern void testThreadPool_MultiThread();

int main() {
    testThreadPool_MultiThread();

    testThreadLambdaExecuteTimeout();
    testThreadLambdaSubmitTimeout();

    testThreadPoolSubmit_ShutDown();
    testThreadPoolSubmit_Wait();

    normalTest();
    sleep(1);
    testRunnable_onInterrupt();
    sleep(1);
    releaseTest();
    sleep(1);
    testThreadShutdown();
    testThreadDestroy();
    testThreadPoolLoopSubmit();
    testThreadLambda();
    testThreadQuickShutDown();
    testPoolReferenceCount();

    st(Thread)::msleep(10*1000);
    return 0;
}