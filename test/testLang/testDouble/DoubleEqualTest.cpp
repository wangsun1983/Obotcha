#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Double.hpp"
#include "StrongPointer.hpp"
#include "IllegalArgumentException.hpp"
#include "NullPointerException.hpp"

using namespace obotcha;

const double EPSINON = 0.00001;

int equaltest() {

  while(1) {
    //case 1
    Double d1 = createDouble(1.1);
    Double d1_1 = createDouble(1.1);

    if(!d1->equals(d1_1)) {
        printf("Double equal special test1-------[Fail] \n");
        break;
    }

    //case 2
    Double d2 = createDouble(1.1);
    Double d2_1 = createDouble(1.2);

    if(d2->equals(d2_1)) {
        printf("Double equal special test2-------[Fail] \n");
        break;
    }

    printf("Double equal special test4-------[Success] \n");
    break;
  }

  while(1) {
    //case 1
    Double d1 = createDouble(1.1);
    Double d1_1 = createDouble(1.1);

    if(d1!= d1_1) {
        printf("Double equal special test5-------[Fail] \n");
        break;
    }

    //case 2
    Double d2 = createDouble(1.1);
    Double d2_1 = createDouble(1.2);

    if(d2 == d2_1) {
        printf("Double equal special test6-------[Fail] \n");
        break;
    }

    //case 3
    Double d3 = createDouble(1.1);
    Double d3_1;
    if(d3 == d3_1) {
      printf("Double equal special test7-------[Fail] \n");
    }


    printf("Double equal special test8-------[Success] \n");
    break;
  }
}
