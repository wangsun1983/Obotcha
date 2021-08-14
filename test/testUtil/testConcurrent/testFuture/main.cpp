#include <stdio.h>
#include <unistd.h>

#include "Object.hpp"

using namespace obotcha;

extern void testThreadPoolExecutor_GetResult();
extern void testThreadPoolExecutor_Cancel();

int main() {
    testThreadPoolExecutor_GetResult();
    //testThreadPoolExecutor_Cancel();
    return 1;
}
