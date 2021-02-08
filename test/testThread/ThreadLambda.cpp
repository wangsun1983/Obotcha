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

int testThreadLambda() {
    while(1) {
        int value = 100;
        Thread t1 = createThread([&value]() {
            value = 1;
        });

        t1->start();
        sleep(1);

        if(value != 1) {
            printf("---[Thread TestLambda case1] [FAILED]--- \n");
            break;
        }

        break;
    }

    printf("---[Thread TestLambda case2] [OK]--- \n");

}
