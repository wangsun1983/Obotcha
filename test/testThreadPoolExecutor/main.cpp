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

int main() {
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
    st(Thread)::sleep(10*1000);
    return 0;
}
