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

int TestStringSubString() {
    
    while(1) {
        String str = createString("abcef");
        String str2 = str->subString(0,2);
        if(!str2->equals("ab") || !str->equals("abcef")) {
            printf("String SubString test1-------[FAIL],str is %s,str2 is %s \n",str->toChars(),str2->toChars());
            break;
        }

        str2 = str->subString(0,1);
        if(!str2->equals("a") || !str->equals("abcef")) {
            printf("String SubString test2-------[FAIL] \n");
            break;
        }

        str2 = str->subString(0,3);
        if(!str2->equals("abc") || !str->equals("abcef")) {
            printf("String SubString test3-------[FAIL] \n");
            break;
        }

        str2 = str->subString(0,4);
        if(!str2->equals("abce") || !str->equals("abcef")) {
            printf("String SubString test4-------[FAIL] \n");
            break;
        }

        str2 = str->subString(0,5);
        if(!str2->equals("abcef") || !str->equals("abcef")) {
            printf("String SubString test5-------[FAIL] \n");
            break;
        }

        str2 = str->subString(0,6);
        if(str2 != nullptr) {
            printf("String SubString test6-------[FAIL] \n");
            break;
        }

        str2 = str->subString(0,-1);
        if(str2 != nullptr) {
            printf("String SubString test7-------[FAIL] \n");
            break;
        }

        str2 = str->subString(-1,3);
        if(str2 != nullptr) {
            printf("String SubString test8-------[FAIL] \n");
            break;
        }
        break;
    }

    printf("String SubString test100-------[OK] \n");
    return 0;
}
