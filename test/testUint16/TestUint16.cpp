#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint16.hpp"
#include "StrongPointer.hpp"

using namespace obotcha;

int main() {

  printf("---[Uint16 Test Start]--- \n");
  //_Uint16(int v);
  while(1) {
      Uint16 v1 = createUint16(10);
      if(v1->toValue() != 10){
          printf("Uint16 construct test1-------[FAIL] \n");
          break;
      }

      printf("Uint16 construct test-------[OK] \n");
      break;
  }

  //  _Uint16(Uint16 v);
  while(1) {
    Uint16 v1 = createUint16(11);
    Uint16 v2 = createUint16(v1);
    if(v2->toValue() != 11) {
      printf("Uint16 construct test3-------[FAIL] \n");
      break;
    }

    Uint16 v3;
    Uint16 v4 = createUint16(v3);
    if(v4->toValue() != 0) {
      printf("Uint16 construct test4-------[FAIL] \n");
      break;
    }

    printf("Uint16 construct test5-------[OK] \n");
    break;
  }

  //int toValue();
  while(1) {
    Uint16 v1 = createUint16(11);
    Uint16 v2 = createUint16(v1);
    if(v2->toValue() != 11) {
      printf("Uint16 toValue test1-------[FAIL] \n");
      break;
    }

    printf("Uint16 toValue test1-------[OK] \n");
    break;
  }

  //bool equals(Uint16 p);
  while(1) {
    Uint16 v1 = createUint16(11);
    Uint16 v2 = createUint16(11);
    if(!v1->equals(v2)) {
      printf("Uint16 equals test1-------[FAIL] \n");
      break;
    }

    if(v1->equals(nullptr)) {
      printf("Uint16 equals test2-------[FAIL] \n");
      break;
    }

    printf("Uint16 equals test3-------[OK] \n");
    break;
  }

  //bool equals(int p);
  while(1) {
    Uint16 v1 = createUint16(11);
    if(!v1->equals(11)) {
      printf("Uint16 equals test4-------[FAIL] \n");
      break;
    }

    printf("Uint16 equals test5-------[OK] \n");
    break;
  }

  //==
  while(1) {
    Uint16 v1 = createUint16(12);
    Uint16 v2 = createUint16(12);
    if(v1 != v2) {
      printf("Uint16 [==] test1-------[FAIL] \n");
      break;
    }

    printf("Uint16 [==] test1-------[OK] \n");
    break;
  }

  //MAX_VALUE/MIN_VALUE
  while(1) {
      if(st(Uint16)::MAX_VALUE < 0) {
        printf("Uint16 MAX_VALUE test1-------[FAIL] \n");
        break;
      }

      if(st(Uint16)::MIN_VALUE != 0) {
        printf("Uint16 MIN_VALUE test2-------[FAIL] \n");
        break;
      }

      printf("Uint16 MIN_VALUE/MAX_VALUE test3-------[Success] \n");
      break;
  }
}
