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

int testMutexInOneThread() {
    //Mutex()
    while(1) {
        Mutex m = createMutex();
        m->lock();
        m->lock();
        printf("---[TestMutex TestMutexInOneThread case1] [Success]--- \n");
        break;
    }

    while(1) {
        Mutex m = createMutex();
        m->tryLock();
        m->lock();
        printf("---[TestMutex TestMutexInOneThread case2] [Success]--- \n");
        break;
    }
}
