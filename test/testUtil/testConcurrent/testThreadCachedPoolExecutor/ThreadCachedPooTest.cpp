#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ThreadCachedPoolExecutor.hpp"
#include "Integer.hpp"
#include "ExecutorBuilder.hpp"
#include "Future.hpp"
#include "System.hpp"

using namespace obotcha;

extern int normalTest();
extern int numTest();
extern int releaseTest();
extern int loopsubmittest();
extern int cancelTest();
extern int testThreadLambda();

int main() {
    normalTest();
    //numTest();
    //releaseTest();
    //loopsubmittest();
    //cancelTest();
    //testThreadLambda();
    sleep(10);
}
