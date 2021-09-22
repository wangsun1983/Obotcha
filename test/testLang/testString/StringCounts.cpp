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

void TestCounts() {

    //----------------------------
    while(1) {
        //case 1
        String str1 = createString("abcbcb");
        String str2 = createString("bc");
        String str3 = createString("b");
        String str4 = createString("q");
        if(str1->counts(str2) != 2) {
            printf("String TestCounts test1-------[FAIL]\n");
            break;
        }

        if(str1->counts(str3) != 3) {
            printf("String TestCounts test2-------[FAIL]\n");
            break;
        }

        if(str1->counts(str4) != 0) {
            printf("String TestCounts test3-------[FAIL]\n");
            break;
        }
        break;
    }

    printf("String TestCounts test100-------[OK]\n");
}
