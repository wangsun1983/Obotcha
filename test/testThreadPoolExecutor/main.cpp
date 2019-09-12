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

int main() {
    normalTest();
    testRunnable_onInterrupt();
    return 1;
}
