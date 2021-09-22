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

void testsafemode() {

  //case1
  while(1) {
    ByteArray arr1 = createByteArray(8);
    arr1->setSafe();
    for(int i = 0;i < 8;i++) {
      arr1[i] = 99;
    }

    byte *data1 = arr1->toValue();
    for(int i = 0;i < 8;i++) {
      data1[i] = i;
    }

    for(int i = 0;i < 8;i++) {
      if(arr1[i] != 99) {
        printf("ByteArray testsafemode test 1-------[FAIL] \n");
        break;
      }
    }
    free(data1);
    
    printf("ByteArray testsafemode test 2-------[OK] \n");
    break;
  }

  //case2
  while(1) {
    ByteArray arr1 = createByteArray(8);
    for(int i = 0;i < 8;i++) {
      arr1[i] = 99;
    }

    byte *data1 = arr1->toValue();
    for(int i = 0;i < 8;i++) {
      data1[i] = i;
    }

    for(int i = 0;i < 8;i++) {
      if(arr1[i] != i) {
        printf("ByteArray testsafemode test 3-------[FAIL] \n");
        break;
      }
    }

    printf("ByteArray testsafemode test 4-------[OK] \n");
    break;
  }

  //case3
  while(1) {
    ByteArray arr1 = createByteArray(8);
    arr1->setSafe();
    if(!arr1->isSafeMode()) {
      printf("ByteArray testsafemode test 5-------[FAILED] \n");
      break;
    }
    break;
  }

  printf("ByteArray testsafemode test 100-------[OK] \n");
  return;
}
