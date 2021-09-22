#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Float.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

void hashcodetest() {
  Float t1 = createFloat(1.1);
  Float t2 = createFloat(1.1);
  if(t1->hashcode() != t2->hashcode()) {
    printf("Float hashcode test1-------[FAIL] \n");
  }

  Float t3 = createFloat(1.10);
  if(t1->hashcode() != t3->hashcode()) {
    printf("Float hashcode test2-------[FAIL] \n");
  }

  Float t4 = createFloat(1.100000001);
  if(t1->hashcode() != t4->hashcode()) {
    printf("Float hashcode test3-------[FAIL] \n");
  }

  printf("Float hashcode test100-------[OK] \n");
}
