#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Boolean.hpp"
#include "StrongPointer.hpp"
#include "IllegalArgumentException.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

int testValueOf() {

    while(1) {
        
        Boolean t1 = st(Boolean)::valueOf("true");
        if(!t1->toValue()) {
            printf("Boolean valueOf test1-------[FAIL] \n");
        }

        Boolean t2 = st(Boolean)::valueOf("false");
        if(t2->toValue()) {
            printf("Boolean valueOf test2-------[FAIL] \n");
        }

        Boolean t3 = st(Boolean)::valueOf("TrUe");
        if(!t3->toValue()) {
            printf("Boolean valueOf test3-------[FAIL] \n");
        }

        Boolean t4 = st(Boolean)::valueOf("tRUe");
        if(!t4->toValue()) {
            printf("Boolean valueOf test4-------[FAIL] \n");
        }

        Boolean t5 = st(Boolean)::valueOf("False");
        if(t5->toValue()) {
            printf("Boolean valueOf test5-------[FAIL] \n");
        }

        Boolean t6 = st(Boolean)::valueOf("FAlse ");
        if(t6->toValue()) {
            printf("Boolean valueOf test6-------[FAIL] \n");
        }

        Boolean t7 = st(Boolean)::valueOf("t r u e ");
        if(!t7->toValue()) {
            printf("Boolean valueOf test7-------[FAIL] \n");
        }

        Boolean t8 = st(Boolean)::valueOf("f a L S e");
        if(t8->toValue()) {
            printf("Boolean valueOf test8-------[FAIL] \n");
        }

        bool isException = false;
        try {
          Boolean t9 = st(Boolean)::valueOf("abc");
        } catch(InitializeException exception) {
          isException = true;
        }

        if(!isException) {
            printf("Boolean valueOf test9-------[FAIL] \n");
        }

        printf("Boolean valueOf test19-------[OK] \n");
        break;
    }

}
