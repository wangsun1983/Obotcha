#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "ByteArray.hpp"
#include "StrongPointer.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "Error.hpp"

using namespace obotcha;

int testConstruct() {

    while(1) {
      //case1 _ByteArray(int length,bool isSafe = false);
      ByteArray data = createByteArray(128);
      if(data->size() != 128) {
        printf("ByteArray test Construct test 1-------[FAIL] \n");
        break;
      }
      data[16] = 12;
      byte *val = data->toValue();
      val[16] = 32;
      if(data[16] != 32) {
        printf("ByteArray test Construct test 2-------[FAIL] \n");
        break;
      }

      data = createByteArray(128,true);
      data[16] = 12;

      val = data->toValue();
      val[16] = 32;
      if(data[16] == 32) {
        printf("ByteArray test Construct test 3-------[FAIL] \n");
        break;
      }

      printf("ByteArray test Construct test 4-------[OK] \n");
      break;
    }

    while(1) {
      //_ByteArray(const byte *data,uint32_t len,bool isSafe = false);
      byte data[128];
      for(int i = 0;i < 128;i++) {
        data[i] = i;
      }

      ByteArray arr1 = createByteArray(data+32,16);
      for(int i = 0;i < 16;i++) {
        if(arr1[i] != i+32) {
          printf("ByteArray test Construct test 3-------[FAIL] \n");
          break;
        }
      }

      byte *val = arr1->toValue();
      val[8] = 32;
      if(arr1[8] != 32) {
        printf("ByteArray test Construct test 4-------[FAIL] \n");
        break;
      }

      arr1 = createByteArray(data+32,16,true);
      for(int i = 0;i < 16;i++) {
        if(arr1[i] != i+32) {
          printf("ByteArray test Construct test 4-------[FAIL] \n");
          break;
        }
      }

      val = arr1->toValue();
      val[8] = 32;
      if(arr1[8] == 32) {
        printf("ByteArray test Construct test 5-------[FAIL] \n");
        break;
      }

      printf("ByteArray test Construct test 5-------[OK] \n");
      break;
    }

    while(1) {
      ByteArray data = createByteArray(32);
      for(int i = 0;i<32;i++) {
        data[i] = i;
      }

      ByteArray arr1 = createByteArray(data);
      for(int i = 0;i<32;i++) {
        if(arr1[i] != i) {
          printf("ByteArray test Construct test 6-------[FAIL] \n");
          break;
        }
      }

      byte *val = arr1->toValue();
      val[16] = 22;
      if(arr1[16] != 22) {
        printf("ByteArray test Construct test 7-------[FAIL] \n");
        break;
      }

      ByteArray arr2 = createByteArray(data,true);
      for(int i = 0;i<32;i++) {
        if(arr2[i] != i) {
          printf("ByteArray test Construct test 8-------[FAIL] \n");
          break;
        }
      }

      val = arr2->toValue();
      val[16] = 22;
      if(arr2[16] == 22) {
        printf("ByteArray test Construct test 9-------[FAIL] \n");
        break;
      }

      printf("ByteArray test Construct test 10-------[OK] \n");
      break;
    }

    return 0;
}
