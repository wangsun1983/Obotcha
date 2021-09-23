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

DECLARE_CLASS(Testdata) {

public:
    int i;
    int j;
};

void testThreadLambda() {
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


    while(1) {
        int value = 100;
        Thread t1 = createThread([&value](int v) {
            if(v == 100) {
               value =123;
            }
        },100);

        t1->start();
        sleep(1);

        if(value != 123) {
            printf("---[Thread TestLambda case2] [FAILED]--- \n");
            break;
        }

        break;
    }

    while(1) {
        int value = 100;
        int result = 1;
        Thread t1 = createThread([&value,&result]() {
            if(value == 100) {
               result =123;
            }
        });

        t1->start();
        sleep(1);

        if(result != 123) {
            printf("---[Thread TestLambda case3] [FAILED]--- \n");
            break;
        }

        break;
    }

    while(1) {
        int value = 100;
        int result = 1;
        Thread t1 = createThread([&value,&result]() {
            if(value == 100) {
               result =123;
            }
        });


        sleep(1);

        if(result == 123) {
            printf("---[Thread TestLambda case4] [FAILED]--- \n");
            break;
        }

        break;
    }

    while(1) {
        Testdata data = createTestdata();
        data->i = 100;
        data->j = 120;

        Thread t1 = createThread([&data]() {
            printf("start t1 \n");
            data->i = 1;
            data->j = 2;
        });
        t1->start();


        sleep(1);

        if(data->i != 1 ||data->j != 2) {
            printf("i is %d,j is %d \n",data->i,data->j);
            printf("---[Thread TestLambda case5] [FAILED]--- \n");
            break;
        }

        break;
    }

    printf("---[Thread TestLambda case6] [OK]--- \n");

}
