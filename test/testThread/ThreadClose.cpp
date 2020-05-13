#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "System.hpp"
#include "Error.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(CCTestThread1) IMPLEMENTS(Thread) {
public:
    void run() {
        //while(1) {
            sleep(1);
            //printf("CCTest run \n");
        //}

    }
};

DECLARE_SIMPLE_CLASS(CloseThread1) IMPLEMENTS(Thread) {
public:
    _CloseThread1(CCTestThread1 t) {
        mTh = t;
    }

    void run() {
        sleep(5);
        //printf("i will kill \n");
        mTh->quit();
    }

private:
    CCTestThread1 mTh;
};

int testThreadClose() {
    while(1) {
        CCTestThread1 t1 = createCCTestThread1();
        t1->start();

        //CloseThread1 c1 = createCloseThread1(t1);
        //c1->start();
        break;
    }

    sleep(10);
    //printf("stop!!! \n");
}
