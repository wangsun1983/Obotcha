#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "ByteArray.hpp"
#include "StrongPointer.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "InitializeException.hpp"
#include "IllegalArgumentException.hpp"
#include "NullPointerException.hpp"

using namespace obotcha;


int basetest() {
  printf("---[Byte Test Start]--- \n");
  //_Byte(Byte v);
  while(1) {
      Byte v1 = createByte(10);
      if(v1->toValue() != 10){
          printf("Byte construct test1-------[FAIL] \n");
          break;
      }

      printf("Byte construct test-------[OK] \n");
      break;
  }

  // _Byte(Byte v);
  while(1) {
    Byte v1 = createByte(11);
    Byte v2 = createByte(v1);
    if(v2->toValue() != 11) {
      printf("Byte construct test3-------[FAIL] \n");
      break;
    }

    printf("Byte construct test5-------[OK] \n");
    break;
  }

  //int toValue();
  while(1) {
    Byte v1 = createByte(11);
    Byte v2 = createByte(v1);
    if(v2->toValue() != 11) {
      printf("Byte toValue test1-------[FAIL] \n");
      break;
    }

    printf("Byte toValue test1-------[OK] \n");
    break;
  }

  //bool equals(Integer p);
  while(1) {
    Byte v1 = createByte(11);
    Byte v2 = createByte(11);
    if(!v1->equals(v2)) {
      printf("Byte equals test1-------[FAIL] \n");
      break;
    }

    printf("Byte equals test3-------[OK] \n");
    break;
  }

  //bool equals(int p);
  while(1) {
    Byte v1 = createByte(11);
    if(!v1->equals(11)) {
      printf("Byte equals test4-------[FAIL] \n");
      break;
    }

    printf("Byte equals test5-------[OK] \n");
    break;
  }

  //==
  while(1) {
    Byte v1 = createByte(12);
    Byte v2 = createByte(12);
    if(v1 != v2) {
      printf("Byte [==] test1-------[FAIL] \n");
      break;
    }

    printf("Byte [==] test1-------[OK] \n");
    break;
  }

}
