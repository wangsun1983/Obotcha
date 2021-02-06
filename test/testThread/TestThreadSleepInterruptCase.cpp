#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "System.hpp"

#define TEST_DEVIATION 50 //ms
#define TEST_SLEEP_INTERVAL 100 //s

static int disposeVal = -1;

using namespace obotcha;

Mutex mySleepMutex;
int mySleepTest1 = 0;

DECLARE_SIMPLE_CLASS(MySleepTest1Thread) IMPLEMENTS(Thread) {
public:
    void run() {
        while(1) {
            sleep(50);
        }
    }

    ~_MySleepTest1Thread() {
        mySleepTest1 = 1;
    }

    void onInterrupt() {
        mySleepTest1 = 2;
    }
};

int testThreadSleepInterrupt() {
    //TestThread onInterrupt case1
    while(1) {
        MySleepTest1Thread thread = createMySleepTest1Thread();
        thread->start();
        sleep(1);
        //thread->quit();
        sleep(1);
         if(mySleepTest1 != 2) {
             printf("---[Thread Test {Sleep Interrupt()} special case1] [FAILED]--- \n");
             break;
         }

         printf("---[Thread Test {Sleep Interrupt()} special case2] [OK]--- \n");
         break;
    }

}
