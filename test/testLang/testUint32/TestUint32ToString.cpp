#include <stdio.h>
#include <unistd.h>
#include <cstdio>
#include <sstream>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint32.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

int testtostring() {
   //test hex
   std::string HexTable[100] = {
     "0","1","2","3","4","5","6","7","8",
     "9","a","b","c","d","e","f","10",
     "11","12","13","14","15","16","17","18",
     "19","1a","1b","1c","1d","1e","1f","20",
     "21","22","23","24","25","26","27","28",
     "29","2a","2b","2c","2d","2e","2f","30",
     "31","32","33","34","35","36","37","38",
     "39","3a","3b","3c","3d","3e","3f","40",
     "41","42","43","44","45","46","47","48",
     "49","4a","4b","4c","4d","4e","4f","50",
     "51","52","53","54","55","56","57","58",
     "59","5a","5b","5c","5d","5e","5f","60",
     "61","62","63"
   };

   std::string OctTable[100] = {
     "0","1","2","3","4","5","6","7","10",
     "11","12","13","14","15","16","17","20",
     "21","22","23","24","25","26","27","30",
     "31","32","33","34","35","36","37","40",
     "41","42","43","44","45","46","47","50",
     "51","52","53","54","55","56","57","60",
     "61","62","63","64","65","66","67","70",
     "71","72","73","74","75","76","77","100",
     "101","102","103","104","105","106","107","110",
     "111","112","113","114","115","116","117","120",
     "121","122","123","124","125","126","127","130",
     "131","132","133","134","135","136","137","140",
     "141","142","143"
    };

   std::string BinaryTable[100] = {
     "0","1","10","11","100","101","110","111","1000",
     "1001","1010","1011","1100","1101","1110","1111","10000",
     "10001","10010","10011","10100","10101","10110","10111","11000",
     "11001","11010","11011","11100","11101","11110","11111","100000",
     "100001","100010","100011","100100","100101","100110","100111","101000",
     "101001","101010","101011","101100","101101","101110","101111","110000",
     "110001","110010","110011","110100","110101","110110","110111","111000",
     "111001","111010","111011","111100","111101","111110","111111","1000000",
     "1000001","1000010","1000011","1000100","1000101","1000110","1000111","1001000",
     "1001001","1001010","1001011","1001100","1001101","1001110","1001111","1010000",
     "1010001","1010010","1010011","1010100","1010101","1010110","1010111","1011000",
     "1011001","1011010","1011011","1011100","1011101","1011110","1011111","1100000",
     "1100001","1100010","1100011",
   };

   //toString
   while(1) {
     for(int i = 0;i < 100;i++) {
       Uint32 t1 = createUint32(i);
       String v1 = t1->toHexString();
       String v2 = createString(HexTable[i]);
       if(v1 != v2) {
         printf("v1 is %s,v2 is %s \n",v1->toChars(),v2->toChars());
         printf("Uint32 toString test1-------[FAIL] \n");
         break;
       }
     }

     for(int i = 0;i < 100;i++) {
       Uint32 t1 = createUint32(i);
       String v1 = t1->toOctalString();

       String v2 = createString(OctTable[i]);
       if(v1 != v2) {
         printf("Uint32 toString test2-------[FAIL] \n");
         break;
       }
     }

     for(int i = 0;i < 100;i++) {
       Uint32 t1 = createUint32(i);
       String v1 = t1->toBinaryString();
       String v2 = createString(BinaryTable[i]);
       if(v1 != v2) {
         printf("Uint32 toString test3-------[FAIL] \n");
         break;
       }
     }

     printf("Uint32 toString test4-------[OK] \n");
     break;
   }

   //toInt
   while(1) {
     for(int i = 0;i < 100;i++) {
       Uint32 t1 = createUint32(i);
       Uint32 t2 = st(Uint32)::parseHexUint32(createString(HexTable[i]));
       Uint32 t3 = createUint32(t2);
       if(t1 != t3) {
         printf("t1 is %d,t3 is %d \n",t1->toValue(),t3->toValue());
         printf("Uint32 toInt test1-------[FAIL] \n");
         break;
       }
     }

     for(int i = 0;i < 100;i++) {
       Uint32 t1 = createUint32(i);
       Uint32 t2 = st(Uint32)::parseOctUint32(createString(OctTable[i]));
       Uint32 t3 = createUint32(t2);

       if(t1 != t3) {
         printf("t1 is %d,t3 is %d,i is %d \n",t1->toValue(),t3->toValue(),i);
         printf("Uint32 toInt test2-------[FAIL] \n");
         break;
       }
     }

     for(int i = 0;i < 100;i++) {
       Uint32 t1 = createUint32(i);
       String str = createString(BinaryTable[i]);
       //printf("11111 str is %s \n",str->toChars());
       Uint32 t2 = st(Uint32)::parseBinaryUint32(str);
       Uint32 t3 = createUint32(t2);
        if(t1 != t3) {
         printf("Uint32 toInt test3-------[FAIL] \n");
         break;
       }
     }

     printf("Uint32 toInt test10-------[OK] \n");
     break;
   }


}
