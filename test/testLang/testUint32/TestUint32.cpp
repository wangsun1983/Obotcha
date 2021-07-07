#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint32.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"
#include "NullPointerException.hpp"

using namespace obotcha;

int basetest() {

  printf("---[Uint32 Test Start]--- \n");
  //_Uint32(int v);
  while(1) {
      Uint32 v1 = createUint32(10);
      if(v1->toValue() != 10){
          printf("Uint32 construct test1-------[FAIL] \n");
          break;
      }

      printf("Uint32 construct test-------[OK] \n");
      break;
  }

  //  _Uint32(Uint32 v);
  while(1) {
    Uint32 v1 = createUint32(11);
    Uint32 v2 = createUint32(v1);
    if(v2->toValue() != 11) {
      printf("Uint32 construct test3-------[FAIL] \n");
      break;
    }

    Uint32 v3;
    try {
        Uint32 v4 = createUint32(v3);
        printf("Uint32 construct test4-------[FAIL] \n");
    } catch(InitializeException e) {}

    printf("Uint32 construct test5-------[OK] \n");
    break;
  }

  //int toValue();
  while(1) {
    Uint32 v1 = createUint32(11);
    Uint32 v2 = createUint32(v1);
    if(v2->toValue() != 11) {
      printf("Uint32 toValue test1-------[FAIL] \n");
      break;
    }

    printf("Uint32 toValue test1-------[OK] \n");
    break;
  }

  //bool equals(Uint32 p);
  while(1) {
    Uint32 v1 = createUint32(11);
    Uint32 v2 = createUint32(11);
    if(!v1->equals(v2)) {
      printf("Uint32 equals test1-------[FAIL] \n");
      break;
    }

    try {
      v1->equals(nullptr);
      printf("Uint32 equals test2-------[FAIL] \n");
    } catch(NullPointerException e) {}

    printf("Uint32 equals test3-------[OK] \n");
    break;
  }

  //bool equals(int p);
  while(1) {
    Uint32 v1 = createUint32(11);
    if(!v1->equals(11)) {
      printf("Uint32 equals test4-------[FAIL] \n");
      break;
    }

    printf("Uint32 equals test5-------[OK] \n");
    break;
  }

  //==
  while(1) {
    Uint32 v1 = createUint32(12);
    Uint32 v2 = createUint32(12);
    if(v1 != v2) {
      printf("Uint32 [==] test1-------[FAIL] \n");
      break;
    }

    printf("Uint32 [==] test1-------[OK] \n");
    break;
  }

  //MAX_VALUE/MIN_VALUE
  while(1) {
      if(st(Uint32)::MAX_VALUE < 0) {
        printf("Uint32 MAX_VALUE test1-------[FAIL] \n");
        break;
      }

      if(st(Uint32)::MIN_VALUE != 0) {
        printf("Uint32 MIN_VALUE test2-------[FAIL] \n");
        break;
      }

      printf("Uint32 MIN_VALUE/MAX_VALUE test3-------[Success] \n");
      break;
  }
}
