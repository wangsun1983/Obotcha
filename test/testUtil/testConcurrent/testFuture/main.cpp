#include <stdio.h>
#include <unistd.h>

#include "Object.hpp"

using namespace obotcha;

extern void testThreadPoolExecutor_GetResult();
extern void testThreadPoolExecutor_Cancel();
extern void testThreadPoolExecutor_GetResult_Error();
extern void testThreadPoolExecutor_GetResult_TimeWatch();
extern void testThreadPoolExecutor_Wait();

int main() {
    //testThreadPoolExecutor_GetResult();
    //testThreadPoolExecutor_Cancel();
    //testThreadPoolExecutor_GetResult_Error();
    //testThreadPoolExecutor_GetResult_TimeWatch();
    testThreadPoolExecutor_Wait();
    return 1;
}
