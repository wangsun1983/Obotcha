#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "Integer.hpp"

using namespace obotcha;

extern void testEnqueueDequeue();
extern void testMultiThreadQueue();
extern void testBlockingQueueInt();

int main() {

    //testEnqueueDequeue();
    //testMultiThreadQueue();
    testBlockingQueueInt();
    return 0;
}
