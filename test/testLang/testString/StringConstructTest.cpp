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

int StringConstructTest() {
    //String append(String s);
    while(1) {
        std::string str = "abc";
        String str1 = createString(&str);
        if(!str1->equals("abc")) {
            printf("String construct test1-------[FAIL] \n");
            break;
        }

        String str2 = createString(str);
        if(!str2->equals("abc")) {
            printf("String construct test2-------[FAIL] \n");
            break;
        }

        String str3 = createString(str2);
        if(!str3->equals("abc")) {
            printf("String construct test3-------[FAIL] \n");
            break;
        }

        String str4 = createString("abc");
        if(!str4->equals("abc")) {
            printf("String construct test4-------[FAIL] \n");
            break;
        }

        String str5 = createString("abcd",1,3);
        if(!str5->equals("bcd")) {
            printf("String construct test5-------[FAIL] \n");
            break;
        }

        bool isException = false;
        try {
            String str5 = createString("abcd",1,6);
        } catch(...) {
            isException = true;
        }

        try {
            String str5 = createString("abcd",-1,6);
        } catch(...) {
            isException = true;
        }

        try {
            String str5 = createString("abcd",-1,-1);
        } catch(...) {
            isException = true;
        }

        if(!isException) {
            printf("String construct test6-------[FAIL] \n");
            break;
        }

        //
        Integer v1 = createInteger(1200);
        String str6 = createString(v1);
        if(!str6->equals("1200")) {
            printf("String construct test7-------[FAIL] \n");
            break;
        }

        //
        Boolean v2 = createBoolean(false);
        String str7 = createString(v2);
        if(!str7->equals("false")) {
            printf("String construct test8-------[FAIL] \n");
            break;
        }

        Boolean v3 = createBoolean(true);
        String str8 = createString(v3);
        if(!str8->equals("true")) {
            printf("String construct test9-------[FAIL] \n");
            break;
        }

/*
        Float v4 = createFloat(100.0001);
        String str9 = createString(v4);
        if(!str9->equals("100.0001")) {
            printf("String construct test10-------[FAIL] str9 is %s\n",str9->toChars());
            break;
        }

        //
        Double v5 = createDouble(200.3322);
        String str10 = createString(v5);
        if(!str10->equals("200.0002")) {
            printf("String construct test11-------[FAIL],str10 is %s \n",str10->toChars());
            break;
        }
*/
        //
        Long v6 = createLong(200);
        String str11 = createString(v6);
        if(!str11->equals("200")) {
            printf("String construct test12-------[FAIL] \n");
            break;
        }

        //
        Uint8 v7 = createUint8(200);
        String str12 = createString(v7);
        if(!str12->equals("200")) {
            printf("String construct test13-------[FAIL] \n");
            break;
        }

        //
        Uint16 v8 = createUint16(12200);
        String str13 = createString(v8);
        if(!str13->equals("12200")) {
            printf("String construct test14-------[FAIL] \n");
            break;
        }

        //
        Uint32 v9 = createUint32(12200);
        String str14 = createString(v9);
        if(!str14->equals("12200")) {
            printf("String construct test15-------[FAIL] \n");
            break;
        }
        
        //
        Uint64 v10 = createUint64(12200);
        String str15 = createString(v10);
        if(!str15->equals("12200")) {
            printf("String construct test16-------[FAIL] \n");
            break;
        }
        
        //
        Byte v11 = createByte(22);
        String str16 = createString(v11);
        if(!str16->equals("22")) {
            printf("String construct test17-------[FAIL] \n");
            break;
        }
        
        //_String(int v);
        int v12 = 100;
        String str17 = createString(v12);
        if(!str17->equals("100")) {
            printf("String construct test18-------[FAIL] \n");
            break;
        }


        //_String(bool v);
        bool v13 = false;
        String str18 = createString(v13);
        if(!str18->equals("false")) {
            printf("String construct test19-------[FAIL] \n");
            break;
        }

        bool v14 = true;
        String str19 = createString(v14);
        if(!str19->equals("true")) {
            printf("String construct test20-------[FAIL] \n");
            break;
        }

/*
        //_String(float v);
        float v15 = 11.112;
        String str20 = createString(v15);
        if(!str20->equals("11.112")) {
            printf("String construct test21-------[FAIL] \n");
            break;
        }

        //_String(double v);
        double v16 = 11.112;
        String str21 = createString(v16);
        if(!str21->equals("11.112")) {
            printf("String construct test22-------[FAIL] \n");
            break;
        }
*/
        //_String(long v);
        long v17 = 1200;
        String str22 = createString(v17);
        if(!str22->equals("1200")) {
            printf("String construct test23-------[FAIL] \n");
            break;
        }

        //_String(char v);
        char v18 = 112;
        String str23 = createString(v18);
        if(!str23->equals("112")) {
            printf("String construct test24-------[FAIL] \n");
            break;
        }

        //_String(uint8_t);
        uint8_t v19 = 112;
        String str24 = createString(v19);
        if(!str24->equals("112")) {
            printf("String construct test25-------[FAIL] \n");
            break;
        }

        //_String(uint16_t);
        uint16_t v20 = 1112;
        String str25 = createString(v20);
        if(!str25->equals("1112")) {
            printf("String construct test26-------[FAIL] \n");
            break;
        }

        //_String(uint32_t);
        uint32_t v21 = 1113332;
        String str26 = createString(v21);
        if(!str26->equals("1113332")) {
            printf("String construct test27-------[FAIL] \n");
            break;
        }
        
        //_String(uint64_t);
        uint32_t v22 = 111334432;
        String str27 = createString(v22);
        if(!str27->equals("111334432")) {
            printf("String construct test28-------[FAIL] \n");
            break;
        }
        
        printf("String construct test100-------[OK] \n");
        break;
    }

    return 0;
}
