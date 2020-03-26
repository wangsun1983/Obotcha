#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "ByteArray.hpp"
#include "StrongPointer.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"

using namespace obotcha;

struct MyData {
  int i;
  int j;
};

int basetest() {

    printf("---[ByteArray Test Start]--- \n");
    while(1) {
        //Test Construct
        ByteArray array1 = createByteArray(16);

        byte *p = array1->toValue();
        for(int index = 0;index++;index<16) {
            if(p[index] != 0) {
              printf("ByteArray construct test1-------[FAIL] \n");
              break;
            }
        }

        byte *v = (byte *)malloc(16);
        memset(v,8,16);
        ByteArray array2 = createByteArray(v,16);
        byte *p2 = array2->toValue();
        bool isOk = true;
        for(int index = 0;index++;index<16) {
            if(p2[index] != 8) {
              printf("ByteArray construct test2-------[FAIL] \n");
              isOk = false;
              break;
            }
        }

        free(v);

        if(isOk) {
            printf("ByteArray construct -------[OK] \n");
        }
        break;
    }

    while(1) {
        //test clear
        byte *v = (byte *)malloc(16);
        memset(v,8,16);
        ByteArray array1 = createByteArray(v,16);
        array1->clear();
        byte *p2 = array1->toValue();
        bool isOk = true;
        for(int index = 0;index++;index<16) {
            if(p2[index] != 0) {
              printf("ByteArray clear test1 -------[FAIL] \n");
              isOk = false;
              break;
            }
        }

        free(v);

        if(isOk) {
            printf("ByteArray clear -------[OK] \n");
        }
        break;
    }

    while(1) {
        //test toValue
        byte *v = (byte *)malloc(16);
        memset(v,8,16);
        ByteArray array1 = createByteArray(v,16);
        array1->clear();
        byte *p2 = array1->toValue();
        bool isOk = true;
        for(int index = 0;index++;index<16) {
            if(p2[index] != 0) {
              printf("ByteArray toValue test1 -------[FAIL] \n");
              isOk = false;
              break;
            }
        }

        free(v);

        if(isOk) {
            printf("ByteArray toValue -------[OK] \n");
        }
        break;
    }

    while(1) {
        //test size
        byte *v = (byte *)malloc(16);
        memset(v,8,16);
        ByteArray array1 = createByteArray(v,16);

        if(array1->size() != 16) {
            printf("ByteArray size test1 -------[FAIL] \n");
            break;
        }

        free(v);

        printf("ByteArray size -------[OK] \n");
        break;
    }

    while(1) {
        //test resize
        byte *v = (byte *)malloc(16);
        memset(v,8,16);
        ByteArray array1 = createByteArray(v,16);
        array1->resize(32);

        if(array1->size() != 32) {
            printf("ByteArray resize test1 -------[FAIL] \n");
            break;
        }

        byte *p2 = array1->toValue();
        bool isOk = true;
        for(int index = 0;index++;index<16) {
            if(p2[index] != 8) {
              printf("ByteArray resize test2 -------[FAIL] \n");
              isOk = false;
              break;
            }
        }

        if(isOk) {
            printf("ByteArray resize -------[OK] \n");
        }

        free(v);
        break;
    }

    while(1) {
        //test isEmpty
        ByteArray t = createByteArray(16);
        if(t->isEmpty()) {
            printf("ByteArray isEmpty -------[FAIL] \n");
            break;
        }

        printf("ByteArray isEmpty -------[OK] \n");
        break;
    }

    while(1) {
        //test at
        byte *v = (byte *)malloc(16);
        memset(v,8,16);
        ByteArray array1 = createByteArray(v,16);
        byte *p = array1->toValue();
        bool isOk = true;
        for(int index = 0;index++;index<16) {
            if(p[index] != array1->at(index)) {
                isOk = false;
                printf("ByteArray at -------[FAIL] \n");
                break;
            }
        }

        if(isOk) {
          printf("ByteArray at -------[OK] \n");
        }
        free(v);
        break;
    }

    while(1) {
        //test at
        byte *v = (byte *)malloc(16);
        memset(v,8,16);
        ByteArray array1 = createByteArray(v,16);
        array1->fill(9);

        byte *p = array1->toValue();
        bool isOk = true;
        for(int index = 0;index++;index<16) {
            if(p[index] != 9) {
                isOk = false;
                printf("ByteArray fill -------[FAIL] \n");
                break;
            }
        }

        if(isOk) {
          printf("ByteArray fill -------[OK] \n");
        }

        free(v);
        break;
    }

    //bool fill(byte v,int index);
    while(1) {
      ByteArray buff1 = createByteArray(6);
      buff1->fill(2,3);

#if 0
      printf("buff1[0] is %d \n",buff1->at(0));
      printf("buff1[1] is %d \n",buff1->at(1));
      printf("buff1[2] is %d \n",buff1->at(2));
      printf("buff1[3] is %d \n",buff1->at(3));
      printf("buff1[4] is %d \n",buff1->at(4));
      printf("buff1[5] is %d \n",buff1->at(5));
#endif
      if(buff1->at(0) != 0
        ||buff1->at(1) != 0
        ||buff1->at(2) != 3
        ||buff1->at(3) != 0
        ||buff1->at(4) != 0
        ||buff1->at(5) != 0) {
          printf("ByteArray fill test 3-------[FAIL] \n");
          break;
      }

      ByteArray buff2 = createByteArray(6);
      buff2->fill(2,2,3);
      if(buff2->at(0) != 0
        ||buff2->at(1) != 0
        ||buff2->at(2) != 3
        ||buff2->at(3) != 3
        ||buff2->at(4) != 0
        ||buff2->at(5) != 0) {
          printf("ByteArray fill test 4-------[FAIL] \n");
          break;
      }

      ByteArray buff3 = createByteArray(6);
      try {
        buff3->fill(100,2,3);
        printf("ByteArray fill test 5-------[FAIL] \n");
      } catch(ArrayIndexOutOfBoundsException e) {}

      ByteArray buff4 = createByteArray(6);
      try {
        buff4->fill(0,200,3);
        printf("ByteArray fill test 6-------[FAIL] \n");
      }catch(ArrayIndexOutOfBoundsException e) {}

      printf("ByteArray fill test 7-------[OK] \n");
      break;
    } 

    //_ByteArray(T t);
    while(1) {
      MyData t;
      t.i = 100;
      t.j = 120;
      ByteArray arr = createByteArray((const byte *) &t,sizeof(struct MyData));
      struct MyData * t1 = (struct MyData *)arr->toValue();
      if(t1->i != t.i
        ||t1->j != t.j) {
          printf("ByteArray construct<template> test 1-------[FAIL] \n");
          break;
      }

      printf("ByteArray construct<template> test 2-------[OK] \n");
      break;
    }

    //char at(int);
    while(1) {
      ByteArray array = createByteArray(2);
      try{
        int value = array->at(3);
        printf("ByteArray at()) test 1-------[FAIL] \n");
        break;
      } catch(ArrayIndexOutOfBoundsException e){
        //printf("exception is %s \n",e->getErrInfo()->toChars());
      }

      printf("ByteArray at()) test 2-------[OK] \n");
      break;
    }

}
