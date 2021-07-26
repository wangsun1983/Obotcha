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

int TestStringToChars() {
    
    while(1) {
        String str = createString("abcdef");
        const char *p = str->toChars();
        if(strlen(p) != str->size()) {
            printf("String toChars test1-------[FAIL] \n");
            break;
        }

        if(p[0] != 'a' || p[1] != 'b' || p[2] != 'c'|| p[3] != 'd' || p[4] != 'e' ||p[5] != 'f') {
            printf("String toChars test2-------[FAIL] \n");
            break;
        }
        
        break;
    }


    printf("String update test100-------[OK] \n");
    return 0;
}
