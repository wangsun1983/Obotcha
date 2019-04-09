#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "ByteArray.hpp"
#include "StrongPointer.hpp"

using namespace obotcha;

int main() {

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

        char *v = (char *)malloc(16);
        memset(v,8,16);
        ByteArray array2 = createByteArray(v,16);
        char *p2 = array2->toValue();
        bool isOk = true;
        for(int index = 0;index++;index<16) {
            if(p2[index] != 8) {
              printf("ByteArray construct test2-------[FAIL] \n");
              isOk = false;
              break;
            }
        }

        if(isOk) {
            printf("ByteArray construct -------[OK] \n");
        }
        break;
    }

    while(1) {
        //test clear
        char *v = (char *)malloc(16);
        memset(v,8,16);
        ByteArray array1 = createByteArray(v,16);
        array1->clear();
        char *p2 = array1->toValue();
        bool isOk = true;
        for(int index = 0;index++;index<16) {
            if(p2[index] != 0) {
              printf("ByteArray clear test1 -------[FAIL] \n");
              isOk = false;
              break;
            }
        }

        if(isOk) {
            printf("ByteArray clear -------[OK] \n");
        }
        break;
    }

    while(1) {
        //test toValue
        char *v = (char *)malloc(16);
        memset(v,8,16);
        ByteArray array1 = createByteArray(v,16);
        array1->clear();
        char *p2 = array1->toValue();
        bool isOk = true;
        for(int index = 0;index++;index<16) {
            if(p2[index] != 0) {
              printf("ByteArray toValue test1 -------[FAIL] \n");
              isOk = false;
              break;
            }
        }

        if(isOk) {
            printf("ByteArray toValue -------[OK] \n");
        }
        break;
    }

    while(1) {
        //test size
        char *v = (char *)malloc(16);
        memset(v,8,16);
        ByteArray array1 = createByteArray(v,16);

        if(array1->size() != 16) {
            printf("ByteArray size test1 -------[FAIL] \n");
            break;
        }

        printf("ByteArray size -------[OK] \n");
        break;
    }

    while(1) {
        //test size
        char *v = (char *)malloc(16);
        memset(v,8,16);
        ByteArray array1 = createByteArray(v,16);
        array1->resize(32);

        if(array1->size() != 32) {
            printf("ByteArray resize test1 -------[FAIL] \n");
            break;
        }

        char *p2 = array1->toValue();
        bool isOk = true;
        for(int index = 0;index++;index<32) {
            if(p2[index] != 0) {
              printf("ByteArray resize test2 -------[FAIL] \n");
              isOk = false;
              break;
            }
        }

        if(isOk) {
            printf("ByteArray size -------[OK] \n");
        }
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
        char *v = (char *)malloc(16);
        memset(v,8,16);
        ByteArray array1 = createByteArray(v,16);
        char *p = array1->toValue();
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
        break;
    }

    while(1) {
        //test at
        char *v = (char *)malloc(16);
        memset(v,8,16);
        ByteArray array1 = createByteArray(v,16);
        array1->fill(9);

        char *p = array1->toValue();
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
        break;
    }
}
