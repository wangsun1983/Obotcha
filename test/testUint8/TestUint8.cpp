#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint8.hpp"
#include "StrongPointer.hpp"
#include "Uint8.hpp"
#include "InitializeException.hpp"
#include "NullPointerException.hpp"

using namespace obotcha;

int basetest() {

  printf("---[Uint8 Test Start]--- \n");
  //_Uint8(int v);
  while(1) {
      Uint8 v1 = createUint8(10);
      if(v1->toValue() != 10){
          printf("Uint8 construct test1-------[FAIL] \n");
          break;
      }

      printf("Uint8 construct test-------[OK] \n");
      break;
  }

  //  _Uint8(Uint8 v);
  while(1) {
    Uint8 v1 = createUint8(11);
    Uint8 v2 = createUint8(v1);
    if(v2->toValue() != 11) {
      printf("Uint8 construct test3-------[FAIL] \n");
      break;
    }

    Uint8 v3;
    try {
      Uint8 v4 = createUint8(v3);
      printf("Uint8 construct test4-------[FAIL] \n");
    } catch(InitializeException e) {}

    printf("Uint8 construct test5-------[OK] \n");
    break;
  }

  //int toValue();
  while(1) {
    Uint8 v1 = createUint8(11);
    Uint8 v2 = createUint8(v1);
    if(v2->toValue() != 11) {
      printf("Uint8 toValue test1-------[FAIL] \n");
      break;
    }

    printf("Uint8 toValue test1-------[OK] \n");
    break;
  }

  //bool equals(Uint8 p);
  while(1) {
    Uint8 v1 = createUint8(11);
    Uint8 v2 = createUint8(11);
    if(!v1->equals(v2)) {
      printf("Uint8 equals test1-------[FAIL] \n");
      break;
    }

    try {
      v1->equals(nullptr);
      printf("Uint8 equals test2-------[FAIL] \n");
    } catch(NullPointerException e) {}

    printf("Uint8 equals test3-------[OK] \n");
    break;
  }

  //bool equals(int p);
  while(1) {
    Uint8 v1 = createUint8(11);
    if(!v1->equals(11)) {
      printf("Uint8 equals test4-------[FAIL] \n");
      break;
    }

    printf("Uint8 equals test5-------[OK] \n");
    break;
  }

  //==
  while(1) {
    Uint8 v1 = createUint8(12);
    Uint8 v2 = createUint8(12);
    if(v1 != v2) {
      printf("Uint8 [==] test1-------[FAIL] \n");
      break;
    }

    printf("Uint8 [==] test1-------[OK] \n");
    break;
  }

  //MAX_VALUE/MIN_VALUE
  while(1) {
      if(st(Uint8)::MAX_VALUE < 0) {
        printf("Uint8 MAX_VALUE test1-------[FAIL] \n");
        break;
      }

      if(st(Uint8)::MIN_VALUE != 0) {
        printf("Uint8 MIN_VALUE test2-------[FAIL] \n");
        break;
      }

      printf("Uint8 MIN_VALUE/MAX_VALUE test3-------[Success] \n");
      break;
  }

}
