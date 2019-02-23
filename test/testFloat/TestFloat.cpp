#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Float.hpp"
#include "StrongPointer.hpp"


int main() {

  printf("---[Float Test Start]--- \n");
  //Test Construct
  Float t0 = createFloat(100.01f);
  Float t0_1 = createFloat(t0);
  if(t0 == t0_1){
    printf("Float construct test1-------[OK] \n");
  } else {
    printf("Float construct test1-------[FAIL] \n");
  }

  //Test bool equals(Float p);
  Float t1 = createFloat(1.2f);
  Float t2 = createFloat(1.2f);

  if(t1->equals(t2)) {
    printf("Float equal test1-------[OK] \n");
  } else {
    printf("Float equal test1-------[FAIL] \n");
  }

  if(t1 == t2) {
    printf("Float operator == test1-------[OK] \n");
  } else {
    printf("Float operator == test1-------[FAIL] \n");
  }

  //Test bool equals(int p);
  Float t3 = createFloat(1.1f);
  if(t3->equals(1.1f)) {
    printf("Float equal test2-------[OK] \n");
  } else {
    printf("Float equal test2-------[FAIL] \n");
  }
}
