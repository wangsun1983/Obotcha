#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Boolean.hpp"
#include "StrongPointer.hpp"
#include "IllegalArgumentException.hpp"

using namespace obotcha;

int testequals() {

    while(1) {
        //case1
        Boolean t0 = createBoolean(true);
        Boolean t0_1 = createBoolean(true);
        //Boolean t2 = createBoolean(nullptr);

        if(t0 != t0_1){
            printf("Boolean special equal test1-------[FAIL] \n");
        }

        //case1
        Boolean t1 = createBoolean(false);
        Boolean t1_1 = createBoolean(false);
        if(t1 != t1_1){
            printf("Boolean special equal test2-------[FAIL] \n");
        }

        //case1
        Boolean t2 = createBoolean(false);
        Boolean t2_1 = createBoolean(true);
        if(t2 == t2_1){
            printf("Boolean special equal test3-------[FAIL] \n");
        }

        printf("Boolean special equal test4-------[OK] \n");
        break;
    }

}
