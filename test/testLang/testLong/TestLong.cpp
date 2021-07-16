#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "Log.hpp"
#include "InitializeException.hpp"
#include "NullPointerException.hpp"

using namespace obotcha;

int basetest() {

  printf("---[Long Test Start]--- \n");
  //_Long(long v);
  while(1) {
      Long v1 = createLong(10);
      if(v1->toValue() != 10){
          printf("Long construct test1-------[FAIL] \n");
          break;
      }

      printf("Long construct test-------[OK] \n");
      break;
  }

  // _Long(Long v);
  while(1) {
    Long v1 = createLong(11);
    Long v2 = createLong(v1);
    if(v2->toValue() != 11) {
      printf("Long construct test3-------[FAIL] \n");
      break;
    }

    Long v3;
    try {
        Long v4 = createLong(v3);
        printf("Long construct test4-------[FAIL] \n");
    } catch(InitializeException e) {}

    printf("Long construct test5-------[OK] \n");
    break;
  }

  //int toValue();
  while(1) {
    Long v1 = createLong(11);
    Long v2 = createLong(v1);
    if(v2->toValue() != 11) {
      printf("Long toValue test1-------[FAIL] \n");
      break;
    }

    printf("Long toValue test1-------[OK] \n");
    break;
  }

  //bool equals(Integer p);
  while(1) {
    Long v1 = createLong(11);
    Long v2 = createLong(11);
    if(!v1->equals(v2)) {
      printf("Long equals test2-------[FAIL] \n");
      break;
    }

    printf("Long equals test2-------[OK] \n");
    break;
  }

  //bool equals(int p);
  while(1) {
    Long v1 = createLong(11);
    if(!v1->equals(11)) {
      printf("Long equals test4-------[FAIL] \n");
      break;
    }

    printf("Long equals test5-------[OK] \n");
    break;
  }

  //==
  while(1) {
    Long v1 = createLong(12);
    Long v2 = createLong(12);
    if(v1 != v2) {
      printf("Long [==] test1-------[FAIL] \n");
      break;
    }

    printf("Long [==] test1-------[OK] \n");
    break;
  }

}
