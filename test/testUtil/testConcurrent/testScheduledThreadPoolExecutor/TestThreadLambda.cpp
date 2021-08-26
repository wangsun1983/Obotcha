#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ThreadPoolExecutor.hpp"
#include "Integer.hpp"
#include "ExecutorBuilder.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"

using namespace obotcha;

int testThreadLambda() {
    ThreadScheduledPoolExecutor t = createExecutorBuilder()->newScheduledThreadPool();
    while(1) {
        long time1 = 0;
        long time2 = st(System)::currentTimeMillis();

        t->submit(5000,[&time1]() {
            printf("testThreadLambda inner log1 \n");
            time1 = st(System)::currentTimeMillis();
            printf("testThreadLambda inner log2 \n");
        });

        sleep(6);
        if(time2 - time1 > 5005 || time1 - time2 > 5005) {
            printf("---[testThreadLambda value case1] [FAIL]--- time2 is %ld,time1 is %ld\n",time2,time1);
            break;
        }
        printf("---[testThreadLambda value case2] [OK]--- \n");
        break;
    }
    printf("testThreadLambda inner start shutdown \n");
    t->shutdown();
    printf("testThreadLambda inner start shutdown1 \n");
    sleep(10);
    printf("testThreadLambda inner start shutdown3 \n");
}
