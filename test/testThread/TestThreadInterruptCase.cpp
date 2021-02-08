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

Mutex myTest1Mutex;
int myTest1 = 0;
int myTest1Interrupt = 0;

DECLARE_SIMPLE_CLASS(MyTest1Thread) IMPLEMENTS(Thread) {
public:
    void run() {
        try {
            printf("start sleep \n");
            sleep();
        }catch(InterruptedException &e){
            printf("start sleep exception \n");
            myTest1Interrupt = 1;
        }
    }

    ~_MyTest1Thread() {
        //printf("m2 \n");
        myTest1 = 1;
    }

};

int testThreadInterruptCase() {
    //TestThread onInterrupt case1
    while(1) {
        MyTest1Thread thread = createMyTest1Thread();
        thread->start();
        sleep(1);
        thread->interrupt();
        thread->join();
        if(myTest1Interrupt != 1) {
            printf("---[Thread Test {Interrupt()} special case1,myTest1Interrupt is %d] [FAILED]--- \n",myTest1Interrupt);
            break;
        }

        printf("---[Thread Test {Interrupt()} special case2] [OK]--- \n");
        break;
    }

}
