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
extern void testBlockingQueueDestroy();
extern void testBlockingQueuePeekFirst();
extern void testBlockingQueuePeekLast();
extern void testBlockingQueueToArray();
extern void testBlockingQueuePutLast();
extern void testBlockingQueuePutFirst();
extern void testBlockingQueueTakeFirst();
extern void testBlockingQueueTakeLast();
extern void testBlockingQueueTryPutFirst();
extern void testBlockingQueueTryPutLast();
extern void testBlockingQueueTryTakeFirst();
extern void testBlockingQueueTryTakeLast();
extern void testBlockingQueueUnlimited();
extern void testBlockingQueueClear();

int main() {
    testEnqueueDequeue();
    testMultiThreadQueue();
    testBlockingQueueInt();
    testBlockingQueueDestroy();
    testBlockingQueuePeekFirst();
    testBlockingQueuePeekLast();
    testBlockingQueueToArray();
    testBlockingQueuePutLast();
    testBlockingQueuePutFirst();
    testBlockingQueueTakeFirst();
    testBlockingQueueTakeLast();
    testBlockingQueueTryPutFirst();
    testBlockingQueueTryPutLast();
    testBlockingQueueTryTakeFirst();
    testBlockingQueueTryTakeLast();
    testBlockingQueueUnlimited();
    testBlockingQueueClear();
    return 0;
}
