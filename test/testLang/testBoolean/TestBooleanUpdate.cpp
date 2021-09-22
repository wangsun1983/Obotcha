#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Boolean.hpp"
#include "StrongPointer.hpp"
#include "IllegalArgumentException.hpp"

using namespace obotcha;

void testUpdate() {

    while(1) {
        //case1
        Boolean t0 = createBoolean(true);
        t0->update(true);
        if(!t0->toValue()) {
            printf("Boolean update test1-------[FAIL] \n");
        }

        t0->update(false);
        if(t0->toValue()) {
            printf("Boolean update test2-------[FAIL] \n");
        }

        t0 = createBoolean(false);
        t0->update(true);
        if(!t0->toValue()) {
            printf("Boolean update test3-------[FAIL] \n");
        }

        t0 = createBoolean(false);
        t0->update(false);
        if(t0->toValue()) {
            printf("Boolean update test4-------[FAIL] \n");
        }

        printf("Boolean update test5-------[OK] \n");
        break;
    }

}
