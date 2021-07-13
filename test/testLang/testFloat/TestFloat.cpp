#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Float.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

int basetest() {

  printf("---[Float Test Start]--- \n");
  //_Float(float v);
  while(1) {
      Float v1 = createFloat(10.12);
      if(v1->toValue() != 10.12f){
          printf("Float construct test1-------[FAIL] \n");
          break;
      }

      printf("Float construct test-------[OK] \n");
      break;
  }

  //  _Float(Float v);
  while(1) {
    Float v1 = createFloat(11.12f);
    Float v2 = createFloat(v1);
    if(v2->toValue() != 11.12f) {
      printf("Float construct test3-------[FAIL] \n");
      break;
    }

    printf("Float construct test5-------[OK] \n");
    break;
  }

  //float toValue();
  while(1) {
    Float v1 = createFloat(11.123f);
    Float v2 = createFloat(v1);
    if(v2->toValue() != 11.123f) {
      printf("Float toValue test1-------[FAIL] \n");
      break;
    }

    printf("Float toValue test1-------[OK] \n");
    break;
  }

  //bool equals(Float p);
  while(1) {
    Float v1 = createFloat(1.123f);
    Float v2 = createFloat(1.123f);
    if(!v1->equals(v2)) {
      printf("Float equals test1-------[FAIL] \n");
      break;
    }

    printf("Float equals test3-------[OK] \n");
    break;
  }

  //bool equals(float p);
  while(1) {
    Float v1 = createFloat(11.22);
    if(!v1->equals(11.22)) {
      printf("Float equals test4-------[FAIL] \n");
      break;
    }

    printf("Float equals test5-------[OK] \n");
    break;
  }

  //==
  while(1) {
    Float v1 = createFloat(12.1);
    Float v2 = createFloat(12.1);
    if(v1 != v2) {
      printf("Float [==] test1-------[FAIL] \n");
      break;
    }

    printf("Float [==] test1-------[OK] \n");
    break;
  }
}
