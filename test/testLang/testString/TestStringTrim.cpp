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

void TestStringTrim() {

    while(1) {
        String str = createString(" abc f ");
        String str1 = str->trim();
        if(str1 == nullptr || !str1->equals("abc f")) {
            printf("String trim test1-------[FAIL] \n");
            break;
        }

        str = createString("      abc f      ");
        str1 = str->trim();
        if(str1 == nullptr || !str1->equals("abc f")) {
            printf("String trim test2-------[FAIL] \n");
            break;
        }

        str = createString("      abc   f      ");
        str1 = str->trim();
        if(str1 == nullptr || !str1->equals("abc   f")) {
            printf("String trim test3-------[FAIL] \n");
            break;
        }

        str = createString("abc   f      ");
        str1 = str->trim();
        if(str1 == nullptr || !str1->equals("abc   f")) {
            printf("String trim test4-------[FAIL] \n");
            break;
        }

        str = createString("    abc   f");
        str1 = str->trim();
        if(str1 == nullptr || !str1->equals("abc   f")) {
            printf("String trim test5-------[FAIL] \n");
            break;
        }

        break;
    }

    printf("String trim test100-------[OK] \n");
}
