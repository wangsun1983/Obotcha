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
#include "PriorityPoolExecutor.hpp"

using namespace obotcha;

extern int priorityPoolNormalTest();
extern int testSequence();
extern int priorityPoolReleaseTest();
extern int priorityPoolInterruptTest();

int main() {
    priorityPoolNormalTest();
    sleep(1);
    testSequence();
    sleep(1);
    priorityPoolReleaseTest();
    sleep(1);
    priorityPoolInterruptTest();
}