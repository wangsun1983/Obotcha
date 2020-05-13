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

extern int normalTest();
extern int numTest();
extern int releaseTest();
extern int loopsubmittest();

int main() {
    //normalTest();
    //numTest();
    //releaseTest();
    loopsubmittest();
    //sleep(10);
}
