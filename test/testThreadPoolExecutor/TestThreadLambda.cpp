#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ThreadPoolExecutor.hpp"
#include "Integer.hpp"
#include "Executors.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"

using namespace obotcha;

int testThreadLambda() {
    ThreadPoolExecutor t = createThreadPoolExecutor();
        
    while(1) {
        int value = 100;
        t->execute([&value]() {
            if(value == 100) {
                value = 123;
            }
        });

        sleep(1);
        if(value != 123) {
            printf("---[testThreadLambda value case1] [FAIL]--- \n");
            break;
        }
        break;
    }

    while(1) {
        int value = 100;
        t->execute([&value](int v) {
            if(v == 100) {
                value = 123;
            }
        },value);

        sleep(1);
        if(value != 123) {
            printf("---[testThreadLambda value case2] [FAIL]--- \n");
        }
        break;
    }

    while(1) {
        int value = 100;
        Future f = t->submit([&value](int v) {
            if(v == 100) {
                value = 123;
            }
        },value);

        f->wait();
        if(value != 123) {
            printf("---[testThreadLambda value case3] [FAIL]--- \n");
        }
        break;
    }

    while(1) {
        Future f = t->submit([]() {
            return 1;
        });

        f->wait();
        int value = f->getResult(-1,100);
        if(value != 100) {
            printf("---[testThreadLambda value case4] [FAIL],value is %d--- \n",value);
        }
        break;
    }

    t->shutdown();
    sleep(1);
    printf("---[testThreadLambda value case5] [OK]--- \n");
}