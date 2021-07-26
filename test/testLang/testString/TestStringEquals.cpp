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

int TestStringEquals() {
    
    while(1) {
        String str = createString(" abc  f ");
        if(!str->equals(" abc  f ")) {
            printf("String equals test1-------[FAIL] \n");
            break;
        }

        if(str->equals("a")) {
            printf("String equals test1_1-------[FAIL] \n");
            break;
        }

        if(str->equals("ab")) {
            printf("String equals test2-------[FAIL] \n");
            break;
        }

        if(str->equals("abc")) {
            printf("String equals test3-------[FAIL] \n");
            break;
        }

        if(str->equals("abc ")) {
            printf("String equals test4-------[FAIL] \n");
            break;
        }

        if(str->equals("abc  f")) {
            printf("String equals test5-------[FAIL] \n");
            break;
        }

        if(str->equals("     abc f      ")) {
            printf("String equals test6-------[FAIL] \n");
            break;
        }

        if(str->equals("A")) {
            printf("String equals test7-------[FAIL] \n");
            break;
        }

        String str2 = createString(" abc  f ");
        if(!str->equals(str2)) {
            printf("String equals test8-------[FAIL] \n");
            break;
        }

        break;
    }

    printf("String equals test100-------[OK] \n");
    return 0;
}
