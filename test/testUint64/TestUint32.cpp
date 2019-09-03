#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint64.hpp"
#include "StrongPointer.hpp"

using namespace obotcha;

int main() {

  printf("---[Uint64 Test Start]--- \n");
  //_Uint64(int v);
  while(1) {
      Uint64 v1 = createUint64(10);
      if(v1->toValue() != 10){
          printf("Uint64 construct test1-------[FAIL] \n");
          break;
      }

      printf("Uint64 construct test-------[OK] \n");
      break;
  }

  //  _Uint64(Uint64 v);
  while(1) {
    Uint64 v1 = createUint64(11);
    Uint64 v2 = createUint64(v1);
    if(v2->toValue() != 11) {
      printf("Uint64 construct test3-------[FAIL] \n");
      break;
    }

    Uint64 v3;
    Uint64 v4 = createUint64(v3);
    if(v4->toValue() != 0) {
      printf("Uint64 construct test4-------[FAIL] \n");
      break;
    }

    printf("Uint64 construct test5-------[OK] \n");
    break;
  }

  //int toValue();
  while(1) {
    Uint64 v1 = createUint64(11);
    Uint64 v2 = createUint64(v1);
    if(v2->toValue() != 11) {
      printf("Uint64 toValue test1-------[FAIL] \n");
      break;
    }

    printf("Uint64 toValue test1-------[OK] \n");
    break;
  }

  //bool equals(Uint64 p);
  while(1) {
    Uint64 v1 = createUint64(11);
    Uint64 v2 = createUint64(11);
    if(!v1->equals(v2)) {
      printf("Uint64 equals test1-------[FAIL] \n");
      break;
    }

    if(v1->equals(nullptr)) {
      printf("Uint64 equals test2-------[FAIL] \n");
      break;
    }

    printf("Uint64 equals test3-------[OK] \n");
    break;
  }

  //bool equals(int p);
  while(1) {
    Uint64 v1 = createUint64(11);
    if(!v1->equals(11)) {
      printf("Uint64 equals test4-------[FAIL] \n");
      break;
    }

    printf("Uint64 equals test5-------[OK] \n");
    break;
  }

  //==
  while(1) {
    Uint64 v1 = createUint64(12);
    Uint64 v2 = createUint64(12);
    if(v1 != v2) {
      printf("Uint64 [==] test1-------[FAIL] \n");
      break;
    }

    printf("Uint64 [==] test1-------[OK] \n");
    break;
  }

  //MAX_VALUE/MIN_VALUE
  while(1) {
      if(st(Uint64)::MAX_VALUE < 0) {
        printf("Uint64 MAX_VALUE test1-------[FAIL] \n");
        break;
      }

      if(st(Uint64)::MIN_VALUE != 0) {
        printf("Uint64 MIN_VALUE test2-------[FAIL] \n");
        break;
      }

      printf("Uint64 MIN_VALUE/MAX_VALUE test3-------[Success] \n");
      break;
  }
}
