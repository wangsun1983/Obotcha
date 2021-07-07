#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Boolean.hpp"
#include "StrongPointer.hpp"
#include "IllegalArgumentException.hpp"
#include "NullPointerException.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

int testLogic() {

    //logicOr
    while(1) {
        //Test simple value
        Boolean t0 = createBoolean(true);
        t0->logicOr(true);
        if(!t0->toValue()) {
            printf("Boolean logicOr test1-------[FAIL] \n");
        }

        t0->logicOr(false);
        if(!t0->toValue()) {
            printf("Boolean logicOr test2-------[FAIL] \n");
        }

        t0 = createBoolean(false);
        t0->logicOr(true);
        if(!t0->toValue()) {
            printf("Boolean logicOr test3-------[FAIL] \n");
        }

        t0 = createBoolean(false);
        t0->logicOr(false);
        if(t0->toValue()) {
            printf("Boolean logicOr test4-------[FAIL] \n");
        }

        //Test class
        t0 = createBoolean(true);
        t0->logicOr(createBoolean(true));
        if(!t0->toValue()) {
            printf("Boolean logicOr test5-------[FAIL] \n");
        }

        t0->logicOr(createBoolean(false));
        if(!t0->toValue()) {
            printf("Boolean logicOr test6-------[FAIL] \n");
        }

        t0 = createBoolean(false);
        t0->logicOr(createBoolean(true));
        if(!t0->toValue()) {
            printf("Boolean logicOr test7-------[FAIL] \n");
        }

        t0 = createBoolean(false);
        t0->logicOr(createBoolean(false));
        if(t0->toValue()) {
            printf("Boolean logicOr test8-------[FAIL] \n");
        }

        printf("Boolean logicOr test9-------[OK] \n");
        break;
    }

    //logicAnd
    while(1) {
        //simple value
        Boolean t0 = createBoolean(true);
        t0->logicAnd(true);
        if(!t0->toValue()) {
            printf("Boolean logicAnd test1-------[FAIL] \n");
        }

        t0->logicAnd(false);
        if(t0->toValue()) {
            printf("Boolean logicAnd test2-------[FAIL] \n");
        }

        t0 = createBoolean(false);
        t0->logicAnd(true);
        if(t0->toValue()) {
            printf("Boolean logicAnd test3-------[FAIL] \n");
        }

        t0->logicOr(false);
        if(t0->toValue()) {
            printf("Boolean logicAnd test4-------[FAIL] \n");
        }

        //class data
        t0 = createBoolean(true);
        t0->logicAnd(createBoolean(true));
        if(!t0->toValue()) {
            printf("Boolean logicAnd test5-------[FAIL] \n");
        }

        t0->logicAnd(createBoolean(false));
        if(t0->toValue()) {
            printf("Boolean logicAnd test6-------[FAIL] \n");
        }

        t0 = createBoolean(false);
        t0->logicAnd(createBoolean(true));
        if(t0->toValue()) {
            printf("Boolean logicAnd test7-------[FAIL] \n");
        }

        t0->logicOr(createBoolean(false));
        if(t0->toValue()) {
            printf("Boolean logicAnd test8-------[FAIL] \n");
        }

        printf("Boolean logicAnd test9-------[OK] \n");
        break;
    }

}
