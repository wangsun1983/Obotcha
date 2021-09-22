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

void basetest() {

    printf("---[Boolean Test Start]--- \n");
    while(1) {
        //Test Construct
        Boolean t0 = createBoolean(true);
        Boolean t0_1 = createBoolean(t0);

        if(t0 != t0_1){
            printf("Boolean construct test1-------[FAIL] \n");
        }

        Boolean t1 = createBoolean(createString("true"));
        if(!t1->toValue()) {
            printf("Boolean construct test2-------[FAIL] \n");
        }

        Boolean t2 = createBoolean(createString("false"));
        if(t2->toValue()) {
            printf("Boolean construct test3-------[FAIL] \n");
        }

        Boolean t3 = createBoolean(createString("TrUe"));
        if(!t3->toValue()) {
            printf("Boolean construct test4-------[FAIL] \n");
        }

        Boolean t4 = createBoolean(createString("tRUe"));
        if(!t4->toValue()) {
            printf("Boolean construct test5-------[FAIL] \n");
        }

        Boolean t5 = createBoolean(createString("False"));
        if(t5->toValue()) {
            printf("Boolean construct test6-------[FAIL] \n");
        }

        Boolean t6 = createBoolean(createString("FAlse "));
        if(t6->toValue()) {
            printf("Boolean construct test6-------[FAIL] \n");
        }

        Boolean t7 = createBoolean(createString("t r u e "));
        if(!t7->toValue()) {
            printf("Boolean construct test7-------[FAIL] \n");
        }

        Boolean t8 = createBoolean(createString("f a L S e"));
        if(t8->toValue()) {
            printf("Boolean construct test8-------[FAIL] \n");
        }

        bool isException = false;
        try {
          Boolean t9 = createBoolean(createString("abc"));
        } catch(InitializeException exception) {
          isException = true;
        }

        if(!isException) {
            printf("Boolean construct test9-------[FAIL] \n");
        }

        printf("Boolean construct test-------[OK] \n");
        break;
    }

     while(1) {
        //Test Construct
        Boolean t0 = createBoolean(true);
        Boolean t0_1 = createBoolean(t0);

        if(t0 != t0_1){
            printf("Boolean construct test10-------[FAIL] \n");
        }

        Boolean t1 = createBoolean("true");
        if(!t1->toValue()) {
            printf("Boolean construct test11-------[FAIL] \n");
        }

        Boolean t2 = createBoolean("false");
        if(t2->toValue()) {
            printf("Boolean construct test12-------[FAIL] \n");
        }

        Boolean t3 = createBoolean("TrUe");
        if(!t3->toValue()) {
            printf("Boolean construct test13-------[FAIL] \n");
        }

        Boolean t4 = createBoolean("tRUe");
        if(!t4->toValue()) {
            printf("Boolean construct test14-------[FAIL] \n");
        }

        Boolean t5 = createBoolean("False");
        if(t5->toValue()) {
            printf("Boolean construct test15-------[FAIL] \n");
        }

        Boolean t6 = createBoolean("FAlse ");
        if(t6->toValue()) {
            printf("Boolean construct test16-------[FAIL] \n");
        }

        Boolean t7 = createBoolean("t r u e ");
        if(!t7->toValue()) {
            printf("Boolean construct test17-------[FAIL] \n");
        }

        Boolean t8 = createBoolean("f a L S e");
        if(t8->toValue()) {
            printf("Boolean construct test18-------[FAIL] \n");
        }

        bool isException = false;
        try {
          Boolean t9 = createBoolean("abc");
        } catch(InitializeException exception) {
          isException = true;
        }

        if(!isException) {
            printf("Boolean construct test19-------[FAIL] \n");
        }

        printf("Boolean construct test20-------[OK] \n");
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

        printf("Boolean equal test-------[OK] \n");
        break;
    }
}
