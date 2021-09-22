#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Float.hpp"
#include "StrongPointer.hpp"
#include "IllegalArgumentException.hpp"
#include "NullPointerException.hpp"

using namespace obotcha;

const float EPSINON = 0.00001;

void updatetest() {

  while(1) {
    //case 1
    Float d1 = createFloat(1.1);
    d1->update(1.2);
    if((d1->toValue() - 1.2) > EPSINON) {
      printf("Float update special test1-------[FAIL] \n");
      break;
    }

    Float d2 = createFloat(1.1);
    Float d2_1 = createFloat(1.2);

    d2->update(d2_1);
    if((d2->toValue() - 1.2) > EPSINON) {
      printf("Float update special test2-------[FAIL] \n");
      break;
    }

    printf("Float update special test3-------[OK] \n");
    break;
  }
}
