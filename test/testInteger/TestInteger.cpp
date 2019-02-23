#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"


int main() {

  printf("---[Integer Test Start]--- \n");
  //Test Construct
  Integer t0 = createInteger(100);
  Integer t0_1 = createInteger(t0);
  if(t0 == t0_1){
    printf("integer construct test1-------[OK] \n");
  } else {
    printf("integer construct test1-------[FAIL] \n");
  }

  //Test bool equals(Integer p);
  Integer t1 = createInteger(10);
  Integer t2 = createInteger(10);

  if(t1->equals(t2)) {
    printf("integer equal test1-------[OK] \n");
  } else {
    printf("integer equal test1-------[FAIL] \n");
  }

  if(t1 == t2) {
    printf("integer operator == test1-------[OK] \n");
  } else {
    printf("integer operator == test1-------[FAIL] \n");
  }

  //Test bool equals(int p);
  Integer t3 = createInteger(1);
  if(t3->equals(1)) {
    printf("integer equal test2-------[OK] \n");
  } else {
    printf("integer equal test2-------[FAIL] \n");
  }
}
