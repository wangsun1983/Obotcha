#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Long.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

void hashcodeTest() {

  while(1) {
    Long t1 = createLong(1);
    Long t2 = createLong(1);
    if(t1->hashcode() != t2->hashcode()) {
      printf("Long hashcode test1-------[FAIL] \n");
      break;
    }

    Long t3 = createLong(2);
    if(t1->hashcode() == t3->hashcode()) {
      printf("Long hashcode test2-------[FAIL] \n");
      break;
    }

    printf("Long hashcode test3-------[OK] \n");
    break;
  }

}
