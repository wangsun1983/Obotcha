#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoMutex.hpp"
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
        printf("my thread run1 \n");
        myTest1Mutex->lock();
        while(1) {
            sleep(10);
        }
    }

    ~_MyTest1Thread() {
        printf("my thread destroy \n");
        myTest1 = 1;
    }

    void onInterrupt() {
        printf("my thread Interrupt \n");
        myTest1Interrupt = 1;
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
        thread->exit();
        sleep(1);
         if(myTest1Interrupt != 1 ||myTest1 != 1) {
             printf("---[Thread Test {Interrupt()} special case1] [FAILED]--- \n");
             break;
         }

         printf("---[Thread Test {Interrupt()} special case2] [Success]--- \n");
         break;
    }

}
