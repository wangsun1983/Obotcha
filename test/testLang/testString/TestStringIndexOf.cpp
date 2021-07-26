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

int TestStringIndexOf() {
    
    while(1) {
        String str = createString(" abc  f ");
        if(str->indexOf("  ") != 4) {
            printf("String indexOf test1-------[FAIL] \n");
            break;
        }

        if(str->indexOf("a") != 1) {
            printf("String indexOf test1_1-------[FAIL] \n");
            break;
        }

        if(str->indexOf("ab") != 1) {
            printf("String indexOf test2-------[FAIL] \n");
            break;
        }

        if(str->indexOf("abc") != 1) {
            printf("String indexOf test3-------[FAIL] \n");
            break;
        }

        if(str->indexOf("abc ") != 1) {
            printf("String indexOf test4-------[FAIL] \n");
            break;
        }

        if(str->indexOf("abc  f") != 1) {
            printf("String indexOf test5-------[FAIL] \n");
            break;
        }

        if(str->indexOf("     abc f      ") != -1) {
            printf("String indexOf test6-------[FAIL] \n");
            break;
        }

        if(str->indexOf("A") != -1) {
            printf("String indexOf test7-------[FAIL] \n");
            break;
        }

        if(str->indexOf('a') != 1) {
            printf("String indexOf test8-------[FAIL] \n");
            break;
        }

        if(str->indexOf('b') != 2) {
            printf("String indexOf test9-------[FAIL] \n");
            break;
        }

        if(str->indexOf(' ') != 0) {
            printf("String indexOf test10-------[FAIL] \n");
            break;
        }

        break;
    }

    printf("String indexOf test100-------[OK] \n");
    return 0;
}
