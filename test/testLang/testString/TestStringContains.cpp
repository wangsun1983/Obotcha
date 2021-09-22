#include <stdio.h>
#include <iostream>
#include <type_traits>

#include <string.h>
#include "String.hpp"
#include "ArrayList.hpp"
#include "NullPointerException.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "IllegalArgumentException.hpp"
#include "TransformException.hpp"
#include "IllegalArgumentException.hpp"

using namespace obotcha;

void TestStringContains() {

    while(1) {
        String str = createString(" abc  f ");
        if(!str->contains("  ")) {
            printf("String contains test1-------[FAIL] \n");
            break;
        }

        if(!str->contains("a")) {
            printf("String contains test1_1-------[FAIL] \n");
            break;
        }

        if(!str->contains("ab")) {
            printf("String contains test2-------[FAIL] \n");
            break;
        }

        if(!str->contains("abc")) {
            printf("String contains test3-------[FAIL] \n");
            break;
        }

        if(!str->contains("abc ")) {
            printf("String contains test4-------[FAIL] \n");
            break;
        }

        if(!str->contains("abc  f")) {
            printf("String contains test5-------[FAIL] \n");
            break;
        }

        if(str->contains("     abc f      ")) {
            printf("String contains test6-------[FAIL] \n");
            break;
        }

        if(str->contains("A")) {
            printf("String contains test7-------[FAIL] \n");
            break;
        }

        break;
    }

    printf("String contains test100-------[OK] \n");
}
