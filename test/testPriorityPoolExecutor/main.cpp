#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ThreadPriorityPoolExecutor.hpp"
#include "Integer.hpp"
#include "Executors.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "InterruptedException.hpp"

using namespace obotcha;

extern int normalTest();
extern int testRunnable_onInterrupt();
extern int releaseTest();
extern int testThreadShutdown();
extern int testThreadDestroy();
extern int testSequence();
extern int testThreadLambda();

int main() {

    normalTest();
    sleep(1);

    testRunnable_onInterrupt();
    sleep(1);
    releaseTest();
    sleep(1);
    testThreadShutdown();
    sleep(1);
    testThreadDestroy();
    sleep(1);
    testSequence();
    sleep(1);
    testThreadLambda();

    sleep(10);
    return 1;
}
