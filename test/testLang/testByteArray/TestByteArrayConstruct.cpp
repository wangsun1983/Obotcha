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

      data = createByteArray(128);
      data->setSafe();
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

      arr1 = createByteArray(data+32,16);
      arr1->setSafe();
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

      ByteArray arr2 = createByteArray(data->toValue(),32);
      arr2->setSafe();
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

    //_ByteArray::_ByteArray(sp<_ByteArray>&data,int start,int len)
    while(1) {
      ByteArray data = createByteArray(32);
      for(int i = 0; i < data->size();i++) {
        data[i] = i;
      }

      ByteArray data1 = createByteArray(data);
      if(data1->size() != 32) {
        printf("ByteArray test Construct test 11-------[FAIL] \n");
        break;
      }

      for(int j = 0;j< data1->size();j++) {
        if(data[j] != data1[j]) {
          printf("ByteArray test Construct test 12-------[FAIL] \n");
          break;
        }
      }
      break;
    }

    while(1) {
      ByteArray data = createByteArray(32);
      for(int i = 0; i < data->size();i++) {
        data[i] = i;
      }

      ByteArray data1 = createByteArray(data,10);
      if(data1->size() != 22) {
        printf("ByteArray test Construct test 13-------[FAIL],data1 is %d \n",data1->size());
        break;
      }

      for(int j = 0;j< data1->size();j++) {
        if(data[j + 10] != data1[j]) {
          printf("ByteArray test Construct test 14 -------[FAIL] \n");
          break;
        }
      }
      break;
    }

    while(1) {
      ByteArray data = createByteArray(32);
      for(int i = 0; i < data->size();i++) {
        data[i] = i;
      }

      ByteArray data1 = createByteArray(data,10,2);
      if(data1->size() != 2) {
        printf("ByteArray test Construct test 15-------[FAIL] \n");
        break;
      }

      for(int j = 0;j< 2;j++) {
        if(data[j + 10] != data1[j]) {
          printf("ByteArray test Construct test 16 -------[FAIL] \n");
          break;
        }
      }
      break;
    }
    printf("ByteArray test Construct test 100 -------[OK] \n");
    return 0;
}
