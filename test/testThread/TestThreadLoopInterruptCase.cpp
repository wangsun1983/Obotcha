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

int myLoopTest1 = 0;

int myLoopTest2 = 0;

DECLARE_SIMPLE_CLASS(MyLoopTest1Thread) IMPLEMENTS(Thread) {
public:
    void run() {
        while(1) {
            
        }
    }

    ~_MyLoopTest1Thread() {
        myLoopTest1 = 1;
    }

    void onInterrupt() {
        myLoopTest1 = 2;
    }
};

DECLARE_SIMPLE_CLASS(MyLoopTest2Thread) IMPLEMENTS(Thread) {
public:
    void run() {
        while(1) {
            st(Thread)::interruptCheck();
        }
    }

    ~_MyLoopTest2Thread() {
        myLoopTest2 = 1;
    }

    void onInterrupt() {
        myLoopTest2 = 2;
    }
};


int testThreadLoopInterrypt() {

#if 0
    //TestThread onInterrupt case1
    while(1) {
        MyLoopTest1Thread thread = createMyLoopTest1Thread();
        thread->start();
        sleep(1);
        thread->quit();
        sleep(1);
         if(myLoopTest1 != 2) {
             printf("---[Thread Test {Loop Interrupt()} special case1] [FAILED]--- \n");
             break;
         }

         printf("---[Thread Test {Loop Interrupt()} special case2] [Success]--- \n");
         break;
    }
#endif
    
    //interruptCheck
    while(1) {
        MyLoopTest2Thread thread = createMyLoopTest2Thread();
        thread->start();
        sleep(1);
        thread->quit();
        sleep(1);
         if(myLoopTest2 != 2) {
             printf("---[Thread Test {interruptCheck()} case1] [FAILED]--- \n");
             break;
         }

         printf("---[Thread Test {interruptCheck()} case2] [Success]--- \n");
         break;
    } 

}
