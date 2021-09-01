#include <stdio.h>
#include <unistd.h>

#include "Object.hpp"

using namespace obotcha;

extern void testThreadPoolExecutor_GetResult();
extern void testThreadPoolExecutor_Cancel();
extern void testThreadPoolExecutor_GetResult_Error();
extern void testThreadPoolExecutor_GetResult_Interrupt();
extern void testThreadPoolExecutor_GetResult_TimeWatch();
extern void testThreadPoolExecutor_Wait();
extern void testThreadPoolExecutor_getStatus();
extern void testThreadPoolExecutor_Multithread();

extern void testCachedPoolExecutor_Cancel();
extern void testCachedPoolExecutor_Multithread();
extern void testCachedPoolExecutor_Wait();
extern void testScheduledPoolExecutor_Wait();
extern void testScheduledPoolExecutor_Cancel();
extern void testScheduledPoolExecutor_Multithread();

extern void testPriorityPoolExecutor_Wait();
extern void testPriorityPoolExecutor_Multithread();
extern void testPriorityPoolExecutor_Cancel();

int main() {
    testPriorityPoolExecutor_Cancel();
    testPriorityPoolExecutor_Wait();
    testPriorityPoolExecutor_Multithread();

    testScheduledPoolExecutor_Multithread();
    testScheduledPoolExecutor_Cancel();
    testScheduledPoolExecutor_Wait();
    testCachedPoolExecutor_Multithread();
    testCachedPoolExecutor_Cancel();
    testCachedPoolExecutor_Wait();

    testThreadPoolExecutor_GetResult_Interrupt();
    testThreadPoolExecutor_getStatus();
    testThreadPoolExecutor_GetResult();
    testThreadPoolExecutor_Cancel();
    testThreadPoolExecutor_GetResult_Error();
    testThreadPoolExecutor_GetResult_TimeWatch();
    testThreadPoolExecutor_Wait();
    testThreadPoolExecutor_Multithread();

    return 1;
}
