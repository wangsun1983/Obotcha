#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Boolean.hpp"
#include "StrongPointer.hpp"
#include "IllegalArgumentException.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

void testparse() {

    while(1) {

        Boolean t1 = st(Boolean)::parse("true");
        if(!t1->toValue()) {
            printf("Boolean parse test1-------[FAIL] \n");
        }

        Boolean t2 = st(Boolean)::parse("false");
        if(t2->toValue()) {
            printf("Boolean parse test2-------[FAIL] \n");
        }

        Boolean t3 = st(Boolean)::parse("TrUe");
        if(!t3->toValue()) {
            printf("Boolean parse test3-------[FAIL] \n");
        }

        Boolean t4 = st(Boolean)::parse("tRUe");
        if(!t4->toValue()) {
            printf("Boolean parse test4-------[FAIL] \n");
        }

        Boolean t5 = st(Boolean)::parse("False");
        if(t5->toValue()) {
            printf("Boolean parse test5-------[FAIL] \n");
        }

        Boolean t6 = st(Boolean)::parse("FAlse ");
        if(t6->toValue()) {
            printf("Boolean parse test6-------[FAIL] \n");
        }

        Boolean t7 = st(Boolean)::parse("t r u e ");
        if(!t7->toValue()) {
            printf("Boolean parse test7-------[FAIL] \n");
        }

        Boolean t8 = st(Boolean)::parse("f a L S e");
        if(t8->toValue()) {
            printf("Boolean parse test8-------[FAIL] \n");
        }

        Boolean t9 = st(Boolean)::parse("abc");
        if(t9 != nullptr) {
            printf("Boolean parse test9-------[FAIL] \n");
        }

        printf("Boolean parse test19-------[OK] \n");
        break;
    }

}
