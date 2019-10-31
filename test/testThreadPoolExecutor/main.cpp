#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ExecutorService.hpp"
#include "Integer.hpp"
#include "Executors.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"

using namespace obotcha;

extern int normalTest();
extern int testRunnable_onInterrupt();
extern int releaseTest();
extern int testThreadShutdown();
extern int testThreadDestroy();

int main() {
    normalTest();
    sleep(1);
    testRunnable_onInterrupt();
    sleep(1);
    releaseTest();
    sleep(10);
    testThreadShutdown();
    testThreadDestroy();
   
    sleep(10);
    return 1;
}
