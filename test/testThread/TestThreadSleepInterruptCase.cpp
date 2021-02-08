#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "System.hpp"
#include "InterruptedException.hpp"

#define TEST_DEVIATION 50 //ms
#define TEST_SLEEP_INTERVAL 100 //s

static int disposeVal = -1;

using namespace obotcha;

Mutex mySleepMutex;
int mySleepExceptionTest1 = 0;
int mySleepReleaseTest1 = 0;

DECLARE_SIMPLE_CLASS(MySleepTest1Thread) IMPLEMENTS(Thread) {
public:
    void run() {
        //while(1) {
            try {
                sleep(50*1000);
            } catch(InterruptedException &e) {
                mySleepExceptionTest1 = 1;
            }
        //}
    }

    ~_MySleepTest1Thread() {
        mySleepReleaseTest1 = 1;
    }

};

int testThreadSleepInterrupt() {
    //TestThread onInterrupt case1
    while(1) {
        {
            MySleepTest1Thread thread = createMySleepTest1Thread();
            thread->start();
            sleep(1);
            thread->interrupt();
            
        }
        sleep(1);

        if(mySleepExceptionTest1 != 1 || mySleepReleaseTest1 != 1) {
            printf("---[Thread Test {Sleep Interrupt()} special case1] [FAILED]--- mySleepExceptionTest1 is %d,mySleepReleaseTest1 is %d\n",
                mySleepExceptionTest1,mySleepReleaseTest1);
            break;
        }

        printf("---[Thread Test {Sleep Interrupt()} special case2] [OK]--- \n");
        break;
    }

}
