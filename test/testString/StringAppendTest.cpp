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

int appendtest() {
    //String append(String s);
    while(1) {
        //case1
        String str1 = "abc";
        String str1_1 = str1->append(createString("a"));
        if(!str1->equals(createString("abc"))) {
            printf("String append Special test1-------[FAIL] \n");
            break;
        }

        if(!str1_1->equals(createString("abca"))) {
            printf("String append Special test1_1-------[FAIL] \n");
            break;
        }

        //case2
        String str2 = "abc";
        String str2_1 = str1->append(nullptr);
        if(!str2_1->equals(createString("abc"))) {
            printf("String append Special test2-------[FAIL] \n");
            break;
        }

        if(!str2_1->equals(createString("abc"))) {
            printf("String append Special test2_1-------[FAIL] \n");
            break;
        }

        //case3
        String str3 = "abc";
        String str3_a;
        String str3_1 = str1->append(str3_a);
        if(!str3_1->equals(createString("abc"))) {
            printf("String append Special test3-------[FAIL] \n");
            break;
        }

        if(!str3_1->equals(createString("abc"))) {
            printf("String append Special test3_1-------[FAIL] \n");
            break;
        }

        printf("String append Special test4-------[Success] \n");
        break;
    }

    //String append(std::string s);
    while(1) {
        //case1
        String str1 = "abc";
        String str1_1 = str1->append(std::string("a"));
        if(!str1->equals(createString("abc"))) {
            printf("String append Special test5-------[FAIL] \n");
            break;
        }

        if(!str1_1->equals(createString("abca"))) {
            printf("String append Special test5_1-------[FAIL] \n");
            break;
        }

        //case2
        String str2 = "abc";
        std::string p;
        String str2_1 = str2->append(p);
        if(!str2->equals(createString("abc"))) {
            printf("String append Special test6-------[FAIL] \n");
            break;
        }

        if(!str2_1->equals(createString("abc"))) {
            printf("String append Special test6_1-------[FAIL] \n");
            break;
        }

        printf("String append Special test7-------[Success] \n");
        break;
    }

    //String append(const char *p);
    while(1) {
        //case1
        String str1 = "abc";
        char *abc = "a";
        String str1_1 = str1->append(abc);
        if(!str1->equals(createString("abc"))) {
            printf("String append Special test8-------[FAIL] \n");
            break;
        }

        if(!str1_1->equals(createString("abca"))) {
            printf("String append Special test8_1-------[FAIL] \n");
            break;
        }

        //case2
        String str2 = "abc";
        String str2_1 = str1->append((char *)nullptr);
        if(!str2_1->equals(createString("abc"))) {
            printf("String append Special test9-------[FAIL] \n");
            break;
        }

        if(!str2_1->equals(createString("abc"))) {

            printf("String append Special test9_1-------[FAIL] \n");
            break;
        }

        printf("String append Special test10-------[Success] \n");
        break;
    }

    //String _String::append(T...args)
    while(1) {
        //case1
        String str1 = createString("a");
        String str2 = str1->append("b","c","d");
        if(!str2->equals("abcd")) {
            printf("String append Special test11_1-------[FAIL] \n");
            break;
        }

        printf("String append Special test11_2-------[Success] \n");
        break;
    }

    

   

}
