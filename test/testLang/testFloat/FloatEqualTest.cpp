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

int equaltest() {

  while(1) {
    //case 1
    Float d1 = createFloat(1.1);
    Float d1_1 = createFloat(1.1);

    if(!d1->equals(d1_1)) {
        printf("Float equal special test1-------[Fail] \n");
        break;
    }

    //case 2
    Float d2 = createFloat(1.1);
    Float d2_1 = createFloat(1.2);

    if(d2->equals(d2_1)) {
        printf("Float equal special test2-------[Fail] \n");
        break;
    }

    printf("Float equal special test4-------[Success] \n");
    break;
  }

  while(1) {
    //case 1
    Float d1 = createFloat(1.1);
    Float d1_1 = createFloat(1.1);

    if(d1!= d1_1) {
        printf("Float equal special test5-------[Fail] \n");
        break;
    }

    //case 2
    Float d2 = createFloat(1.1);
    Float d2_1 = createFloat(1.2);

    if(d2 == d2_1) {
        printf("Float equal special test6-------[Fail] \n");
        break;
    }

    //case 3
    Float d3 = createFloat(1.1);
    Float d3_1;
    if(d3 == d3_1) {
      printf("Float equal special test7-------[Fail] \n");
    }


    printf("Float equal special test8-------[Success] \n");
    break;
  }
}
