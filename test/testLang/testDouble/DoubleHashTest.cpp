#include <stdio.h>
#include <unistd.h>
#include <iostream>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Double.hpp"
#include "StrongPointer.hpp"
#include "IllegalArgumentException.hpp"

using namespace obotcha;

const double EPSINON = 0.00001;

void hashtest() {
  Double d1 = createDouble(1.1);
  Double d2 = createDouble(1.1);
  if(d1->hashcode() != d2->hashcode()) {
    printf("Double hashcode test1-------[Fail] \n");
  }

  Double d3 = createDouble(1.10);
  if(d1->hashcode() != d3->hashcode()) {
    printf("Double hashcode test2-------[Fail] \n");
  }

  Double d4 = createDouble(1.100000001);
  if(d1->hashcode() == d4->hashcode()) {
    printf("Double hashcode test3-------[Fail] \n");
  }

  printf("Double hashcode test100-------[OK] \n");
}
