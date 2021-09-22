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

void TestStringTrimAll() {

    while(1) {
        String str = createString(" abc f ");
        String str1 = str->trimAll();
        if(str1 == nullptr || !str1->equals("abcf")) {
            printf("String trimAll test1-------[FAIL] \n");
            break;
        }

        str = createString("      abc f      ");
        str1 = str->trimAll();
        if(str1 == nullptr || !str1->equals("abcf")) {
            printf("String trimAll test2-------[FAIL] \n");
            break;
        }

        str = createString("      abc   f      ");
        str1 = str->trimAll();
        if(str1 == nullptr || !str1->equals("abcf")) {
            printf("String trimAll test3-------[FAIL] \n");
            break;
        }

        str = createString("abc   f      ");
        str1 = str->trimAll();
        if(str1 == nullptr || !str1->equals("abcf")) {
            printf("String trimAll test4-------[FAIL] \n");
            break;
        }

        str = createString("    abc   f");
        str1 = str->trimAll();
        if(str1 == nullptr || !str1->equals("abcf")) {
            printf("String trimAll test5-------[FAIL] \n");
            break;
        }

        break;
    }

    printf("String trimAll test100-------[OK] \n");
}
