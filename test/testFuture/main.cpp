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

using namespace obotcha;

extern int testThreadExecutorPoolFutureCancel();
extern int testThreadCachedPoolFutureCancel();
extern int testFutureNormal();

int main() {
    printf("---[TestFuture Test Start]--- \n");
    //testThreadExecutorPoolFutureCancel();
    //testFutureNormal();
    testThreadCachedPoolFutureCancel();
    sleep(10);
}
