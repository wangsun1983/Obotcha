#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

int hashcodeTest() {

  while(1) {
    Integer t1 = createInteger(1);
    Integer t2 = createInteger(1);
    if(t1->hashcode() != t2->hashcode()) {
      printf("Integer hashcode test1-------[FAIL] \n");
      break;
    }

    Integer t3 = createInteger(2);
    if(t1->hashcode() == t3->hashcode()) {
      printf("Integer hashcode test2-------[FAIL] \n");
      break;
    }

    printf("Integer hashcode test3-------[OK] \n");
    break;
  }

}
