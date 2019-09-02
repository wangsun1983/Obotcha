#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Double.hpp"
#include "StrongPointer.hpp"

using namespace obotcha;

int main() {

  printf("---[Double Test Start]--- \n");
  //Test Construct
  Double t0 = createDouble(100.01);
  Double t0_1 = createDouble(t0);
  if(t0 == t0_1){
    printf("Double construct test1-------[OK] \n");
  } else {
    printf("Double construct test1-------[FAIL] \n");
  }

  //Test bool equals(Double p);
  Double t1 = createDouble(1.2);
  Double t2 = createDouble(1.2);

  if(t1->equals(t2)) {
    printf("Double equal test1-------[OK] \n");
  } else {
    printf("Double equal test1-------[FAIL] \n");
  }

  if(t1 == t2) {
    printf("Double operator == test1-------[OK] \n");
  } else {
    printf("Double operator == test1-------[FAIL] \n");
  }

  //Test bool equals(int p);
  Double t3 = createDouble(1.1);
  if(t3->equals(1.1)) {
    printf("Double equal test2-------[OK] \n");
  } else {
    printf("Double equal test2-------[FAIL] \n");
  }
}
