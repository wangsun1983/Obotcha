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

DECLARE_CLASS(StartTestThread1) IMPLEMENTS(Thread) {
public:
    void run() {
        //printf("startTest trace1 \n");
        sleep(1);
        //printf("startTest trace2 \n");
    }
};

DECLARE_CLASS(StartTestThread2) IMPLEMENTS(Thread) {
public:
    _StartTestThread2() {

    }

    void run() {
        //printf("startTest trace1 \n");
        sleep(1);
        //printf("startTest trace2 \n");
    }
};

DECLARE_CLASS(StartTestThread3) IMPLEMENTS(Thread) {
public:
    void run() {

    }
};

int testThreadStart() {

    while(1) {
        StartTestThread1 t1 = createStartTestThread1();
        t1->start();
        int ret = t1->start();
        if(ret != -AlreadyExecute) {
            printf("---[Thread TestStart {start()} case1] [FAILED]--- \n");
            break;
        }

        sleep(2);
        ret = t1->start();
        if(ret != -AlreadyExecute) {
            printf("---[Thread TestStart {start()} case2] [FAILED]--- \n");
            break;
        }

        printf("---[Thread TestStart {start()} case3] [OK]--- \n");
        break;
    }

    while(1) {
        StartTestThread1 t1 = createStartTestThread1();
        t1->start();
        int ret = t1->start();
        if(ret != -AlreadyExecute) {
            printf("---[Thread TestStart {start()} case4] [FAILED]--- \n");
            break;
        }

        printf("---[Thread TestStart {start()} case5] [OK]--- \n");
        break;
    }

    while(1) {
        Thread t1 = createThread([](){
            sleep(1);
        });
        t1->start();
        int ret = t1->start();
        if(ret != -AlreadyExecute) {
            printf("---[Thread TestStart {start()} case6] [FAILED]--- \n");
            break;
        }

        printf("---[Thread TestStart {start()} case7] [OK]--- \n");
        break;
    }

    while(1) {
        for(int i = 0;i<1024*32;i++) {
            StartTestThread3 r = createStartTestThread3();
            if(r->start() != 0) {
                printf("---[Thread TestStart {start()} case8] [FAILED]--- \n");
                break;
            }

            if(r->start() != -AlreadyExecute) {
                printf("---[Thread TestStart {start()} case9] [FAILED]--- \n");
                break;
            }
        }
        break;
    }

}
