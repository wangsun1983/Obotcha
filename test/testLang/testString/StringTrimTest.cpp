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

int trimtest() {
    
    //String trim();
    while(1) {
        //case1
        String string1 = "a b c";
        String string1_1 = string1->trim();
        if(!string1_1->equals("a b c")) {
            printf("String trim Special test1-------[FAIL] \n");
        }

        if(!string1->equals("a b c")) {
            printf("String trim Special test1_1-------[FAIL] \n");
        }

        //case2
        String string2 = " a b c";
        String string2_1 = string2->trim();
        if(!string2_1->equals("a b c")) {
            printf("String trim Special test2-------[FAIL] \n");
            break;
        }

        if(!string2->equals(" a b c")) {
            printf("String trim Special test2_1-------[FAIL] \n");
        }

        //case3
        String string3 = " a b c ";
        String string3_1 = string3->trim();
        if(!string3_1->equals("a b c")) {
            printf("String trim Special test3-------[FAIL] \n");
            break;
        }

        if(!string3->equals(" a b c ")) {
            printf("String trim Special test3_1-------[FAIL] \n");
        }

        printf("String trim Special test12-------[Success] \n");
        break;
    }

    //String trimAll();
     while(1) {
        //case1
        String string1 = "a b c";
        String string1_1 = string1->trimAll();
        if(!string1_1->equals("abc")) {
            printf("String trimAll Special test1-------[FAIL] \n");
        }

        if(!string1->equals("a b c")) {
            printf("String trimAll Special test1_1-------[FAIL] \n");
        }

        //case2
        String string2 = " a b c";
        String string2_1 = string2->trimAll();
        if(!string2_1->equals("abc")) {
            printf("String trimAll Special test2-------[FAIL] \n");
            break;
        }

        if(!string2->equals(" a b c")) {
            printf("String trimAll Special test2_1-------[FAIL] \n");
        }

        //case3
        String string3 = " a b c ";
        String string3_1 = string3->trimAll();
        if(!string3_1->equals("abc")) {
            printf("String trimAll Special test3-------[FAIL] \n");
            break;
        }

        if(!string3->equals(" a b c ")) {
            printf("String trimAll Special test3_1-------[FAIL] \n");
        }

        printf("String trimAll Special test12-------[Success] \n");
        break;
    }

   

}
