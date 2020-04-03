#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Double.hpp"
#include "StrongPointer.hpp"
#include "IllegalArgumentException.hpp"

using namespace obotcha;

const double EPSINON = 0.00001;

int updatetest() {

  while(1) {
    //case 1
    Double d1 = createDouble(1.1);
    d1->update(1.2);
    if((d1->toValue() - 1.2) > EPSINON) {
      printf("Double update special test1-------[FAIL] \n");
      break;
    }

    Double d2 = createDouble(1.1);
    Double d2_1 = createDouble(1.2);

    d2->update(d2_1);
    if((d2->toValue() - 1.2) > EPSINON) {
      printf("Double update special test2-------[FAIL] \n");
      break;
    }

    Double d3 = createDouble(1.1);
    Double d3_1;
    try{
      d3->update(d3_1);
    } catch(IllegalArgumentException e){}

    printf("Double update special test3-------[OK] \n");
    break;
  }
}
