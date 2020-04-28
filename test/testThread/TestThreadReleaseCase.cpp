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

Mutex myReleaseMutex = createMutex();
int mReleaseCount = 0;

DECLARE_SIMPLE_CLASS(MyReleaseTestThread) IMPLEMENTS(Thread) {
public:
    void run() {
            sleep(1);
    }

    ~_MyReleaseTestThread() {
        AutoMutex l(myReleaseMutex);
        mReleaseCount++;
    }

    void onInterrupt() {

    }

};



DECLARE_SIMPLE_CLASS(MyReleaseTest2Thread) IMPLEMENTS(Thread) {
public:
    void run() {
            sleep(3);
    }

    ~_MyReleaseTest2Thread() {
        AutoMutex l(myReleaseMutex);
        mReleaseCount++;
    }

    void onInterrupt() {

    }
};

int testThreadRelease() {
    //TestThread onInterrupt case1
    while(1) {
        for(int i = 0;i < 50;i++) {
            Thread t = createMyReleaseTestThread();
            t->start();
        }

        sleep(10);
        if(mReleaseCount != 50) {
            printf("---[Thread Test {release()} case1],mReleaseCount is %d [FAILED]--- \n",mReleaseCount);
            break;
        }

        printf("---[Thread Test {release()} case2] [OK]--- \n");
        break;
    }

    while(1) {
        mReleaseCount = 0;
        ArrayList<Thread> list = createArrayList<Thread>();
        for(int i = 0;i < 50;i++) {
            Thread t = createMyReleaseTestThread();
            t->start();
            list->add(t);
        }

        sleep(10);
        if(mReleaseCount != 0) {
            printf("---[Thread Test {release()} case3],mReleaseCount is %d [FAILED]--- \n",mReleaseCount);
            break;
        }

        list->clear();
        if(mReleaseCount != 50) {
            printf("---[Thread Test {release()} case4],mReleaseCount is %d [FAILED]--- \n",mReleaseCount);
            break;
        }

        printf("---[Thread Test {release()} case5] [OK]--- \n");
        break;
    }

    //interrupt
    while(1) {
        mReleaseCount = 0;
        ArrayList<Thread> list = createArrayList<Thread>();
        for(int i = 0;i < 50;i++) {
            Thread t = createMyReleaseTest2Thread();
            t->start();
            list->add(t);
        }

        for(int i = 0;i<50;i++) {
            Thread t = list->get(0);
            t->quit();
        }

        sleep(5);
        if(mReleaseCount != 0) {
            printf("---[Thread Test {release()} case6],mReleaseCount is %d [FAILED]--- \n",mReleaseCount);
            break;
        }

        sleep(5);
        list->clear();
        if(mReleaseCount != 50) {
            printf("---[Thread Test {release()} case7],mReleaseCount is %d [FAILED]--- \n",mReleaseCount);
            break;
        }

        printf("---[Thread Test {release()} case8] [OK]--- \n");
        break;

    }

}
