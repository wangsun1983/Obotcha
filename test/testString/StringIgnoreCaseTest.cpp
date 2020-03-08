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

int ignorecasetest() {
    
    //bool equalsIgnoreCase(String str);
    while(1) {
        //case1
        String testString = createString("ABCDE");
        char value[6] = {'A','B','C','D','E',0x0};
        char value2[6];
        value2[0] = value[0] - 32;
        value2[1] = value[1] - 32;
        value2[2] = value[2] - 32;
        value2[3] = value[3] - 32;
        value2[4] = value[4] - 32;
        value2[5] = 0x0;

        String test1 = createString(value2);

        if(testString->equalsIgnoreCase(test1)) {
            printf("String equalsIgnoreCase Special test1-------[FAIL] is %s\n",test1->toChars());
            break;
        }

        //case2
        char value3[6] = {'a','b','c','d','e',0x0};
        String test3 = createString(value3);

        if(!testString->equalsIgnoreCase(test3)) {
            printf("String equalsIgnoreCase Special test2-------[FAIL] is %s\n",test3->toChars());
            break;
        }

        //case3
        char value4[6] = {'a','b','c',0x0};
        String test4 = createString(value4);

        if(testString->equalsIgnoreCase(test4)) {
            printf("String equalsIgnoreCase Special test4-------[FAIL] is %s\n",test3->toChars());
            break;
        }

        //case4
        try {
            String tmp;
            testString->equalsIgnoreCase(tmp);
            printf("String equalsIgnoreCase Special test5-------[FAIL] is %s\n",test3->toChars());
            break;
        } catch(IllegalArgumentException e) {}

        
        printf("String equalsIgnoreCase Special test6-------[Success] \n");
        break;
    }

    //bool equalsIgnoreCase(std::string str);

    //bool equalsIgnoreCase(const char * str);

}
