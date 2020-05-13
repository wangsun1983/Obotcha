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

Mutex myTest1Mutex;
int myTest1 = 0;
int myTest1Interrupt = 0;

DECLARE_SIMPLE_CLASS(MyTest1Thread) IMPLEMENTS(Thread) {
public:
    void run() {
        //printf("m1 \n");
        myTest1Mutex->lock(500);
        //printf("m1_1 \n");
        while(1) {
            //printf("m1_2 \n");
            sleep(5);
            //printf("m1_3 \n");
        }
    }

    ~_MyTest1Thread() {
        //printf("m2 \n");
        myTest1 = 1;
    }

    void onInterrupt() {
        //printf("m3 \n");
        myTest1Interrupt = 2;
    }
};

int testThreadInterruptCase() {
    //TestThread onInterrupt case1
    while(1) {
        myTest1Mutex = createMutex();
        myTest1Mutex->lock();
        MyTest1Thread thread = createMyTest1Thread();
        thread->start();
        sleep(1);
        thread->quit();
        sleep(1);
         if(myTest1Interrupt != 2) {
             printf("---[Thread Test {Interrupt()} special case1,myTest1Interrupt is %d] [FAILED]--- \n",myTest1Interrupt);
             break;
         }

         printf("---[Thread Test {Interrupt()} special case2] [OK]--- \n");
         break;
    }

}
