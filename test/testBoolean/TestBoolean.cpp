#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Boolean.hpp"
#include "StrongPointer.hpp"
#include "IllegalArgumentException.hpp"
#include "NullPointerException.hpp"

using namespace obotcha;

int basetest() {

    printf("---[Boolean Test Start]--- \n");
    while(1) {
        //Test Construct
        Boolean t0 = createBoolean(true);
        Boolean t0_1 = createBoolean(t0);
        //Boolean t2 = createBoolean(nullptr);

        if(t0 != t0_1){
            printf("Boolean construct test1-------[FAIL] \n");
        }

        //if(t0 == t2) {
        //    printf("Boolean construct test2-------[FAIL] \n");
        //}

        printf("Boolean construct test-------[OK] \n");
        break;
    }

    //Test bool equals(Boolean p);
    while(1){
        Boolean t1 = createBoolean(false);
        Boolean t2 = createBoolean(false);
        Boolean t3 = createBoolean(true);

        if(!t1->equals(t2)) {
            printf("Boolean equal test1-------[FAIL] \n");
        }

        if(t1 != t2){
            printf("Boolean operator test2-------[FAIL] \n");
        }

        if(t2->equals(t3)) {
            printf("Boolean equal test3-------[FAIL] \n");
        }

        if(t2 == t3) {
            printf("Boolean equal test4-------[FAIL] \n");
        }

        if(t2 == nullptr) {
            printf("Boolean equal test5-------[FAIL] \n");
        }

        if(!t1->equals(false) || !t2->equals(false) || !t3->equals(true)) {
            printf("Boolean equal test6-------[FAIL] \n");
        }

        try {
           t1->equals(nullptr);
           printf("Boolean equal test7-------[FAIL] \n");
        } catch(NullPointerException e) {}

        printf("Boolean equal test-------[OK] \n");
        break;
    }
}
