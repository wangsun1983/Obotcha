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
extern int testThreadScheduleFutureCancel();
extern int testFutureNormal();
extern int testThreadExecutorPoolFutureDelayCancel();

int main() {
    printf("---[TestFuture Test Start]--- \n");
    //testThreadExecutorPoolFutureCancel();
    //testFutureNormal();
    //testThreadCachedPoolFutureCancel();
    //testThreadScheduleFutureCancel();
    testThreadExecutorPoolFutureDelayCancel();
    sleep(10);
    printf("end !!!!!!!!\n");
    //while(1) {}
}
