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

void equaltest() {

    //----------------------------
    while(1) {
        //case 1
        String str1 = createString("abc");
        String str2 = createString("abc");
        if(str1 != str2) {
            printf("String equaltest Special test1-------[FAIL]\n");
            break;
        }

        printf("String equaltest Special test2-------[Success]\n");
        break;
    }

}
