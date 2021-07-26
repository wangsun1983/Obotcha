#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Integer.hpp"

using namespace obotcha;

extern int testEnqueueDequeue();
extern int testMultiThreadQueue();

int main() {

    testEnqueueDequeue();
    testMultiThreadQueue();

}
