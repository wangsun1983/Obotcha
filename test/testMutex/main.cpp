#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "Integer.hpp"
#include "AutoLock.hpp"
#include "Mutex.hpp"
#include "System.hpp"

using namespace obotcha;

extern int testMutexNormal();
extern int testMutexInOneThread();

int main() {
    printf("---[TestMutex Test Start]--- \n");
    testMutexInOneThread();
    testMutexNormal();
}
