#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

int basetest() {

  printf("---[Integer Test Start]--- \n");
  //_Integer(int v);
  while(1) {
      Integer v1 = createInteger(10);
      if(v1->toValue() != 10){
          printf("Integer construct test1-------[FAIL] \n");
          break;
      }

      printf("Boolean construct test-------[OK] \n");
      break;
  }

  //  _Integer(Integer v);
  while(1) {
    Integer v1 = createInteger(11);
    Integer v2 = createInteger(v1);
    if(v2->toValue() != 11) {
      printf("Integer construct test3-------[FAIL] \n");
      break;
    }

    Integer v3;
    try {
      Integer v4 = createInteger(v3);
      printf("Integer construct test4-------[FAIL] \n");
    } catch(InitializeException e) {}
    
    printf("Integer construct test5-------[OK] \n");
    break;
  }

  //int toValue();
  while(1) {
    Integer v1 = createInteger(11);
    Integer v2 = createInteger(v1);
    if(v2->toValue() != 11) {
      printf("Integer toValue test1-------[FAIL] \n");
      break;
    }

    printf("Integer toValue test1-------[OK] \n");
    break;
  }

  //bool equals(Integer p);
  while(1) {
    Integer v1 = createInteger(11);
    Integer v2 = createInteger(11);
    if(!v1->equals(v2)) {
      printf("Integer equals test1-------[FAIL] \n");
      break;
    }

    if(v1->equals(nullptr)) {
      printf("Integer equals test2-------[FAIL] \n");
      break;
    }

    printf("Integer equals test3-------[OK] \n");
    break;
  }

  //bool equals(int p);
  while(1) {
    Integer v1 = createInteger(11);
    if(!v1->equals(11)) {
      printf("Integer equals test4-------[FAIL] \n");
      break;
    }

    printf("Integer equals test5-------[OK] \n");
    break;
  }

  //==
  while(1) {
    Integer v1 = createInteger(12);
    Integer v2 = createInteger(12);
    if(v1 != v2) {
      printf("Integer [==] test1-------[FAIL] \n");
      break;
    }

    printf("Integer [==] test1-------[OK] \n");
    break;
  }

}
