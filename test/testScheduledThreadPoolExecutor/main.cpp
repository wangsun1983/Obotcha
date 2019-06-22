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


extern int baseTest();
extern int scheduleTest();

int main() {
    printf("---[TestScheduledThreadPoolExecutor Test Start]--- \n");
    baseTest();
    scheduleTest();
    
}

