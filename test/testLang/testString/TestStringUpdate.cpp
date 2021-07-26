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

int TestStringUpdate() {
    
    /*
    void update(const char *);

    void update(const sp<_String> &str);

    void update(std::string);
    */
    while(1) {
        String str = createString("abc");
        const char *q = "hello";
        str->update(q);

        if(!str->equals("hello")) {
            printf("String update test1-------[FAIL] \n");
            break;
        }

        String str2 = createString("abc");
        char q2[16];
        memset(q2,0,16);
        q2[0] = '1';
        q2[1] = '2';
        q2[2] = '3';
        q2[3] = '4';
        q2[4] = '5';
        str2->update(q2);
        if(!str2->equals("12345")) {
            printf("String update test2-------[FAIL] \n");
            break;
        }

        q2[0] = '9';
        q2[1] = '9';
        q2[2] = '9';
        q2[3] = '9';
        q2[4] = '9';
        if(!str2->equals("12345")) {
            printf("String update test3-------[FAIL] \n");
            break;
        }

        String str3 = createString("abc");
        str3->update("hhhh");
        if(!str3->equals("hhhh")) {
            printf("String update test4-------[FAIL] \n");
            break;
        }

        break;
    }

    while(1) {
        String str = createString("abc");
        String str2 = createString("ffff");
        str2->update(str);
        if(!str2->equals("abc")) {
            printf("String update test4-------[FAIL] \n");
            break;
        }

        str->update("ttt");
        if(!str2->equals("abc")) {
            printf("String update test5-------[FAIL] \n");
            break;
        }
        break;
    }

    while(1) {
        String str = createString("abc");
        std::string str2 = "ffff";
        str->update(str2);

        if(!str->equals("ffff")) {
            printf("String update test6-------[FAIL] \n");
            break;
        }

        break;
    }


    printf("String update test100-------[OK] \n");
    return 0;
}
