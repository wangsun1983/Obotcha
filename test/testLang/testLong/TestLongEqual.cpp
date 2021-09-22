#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Long.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"
#include "Long.hpp"

using namespace obotcha;

void equaltest() {

  while(1) {
      Long v1 = createLong(10);
      Long v2 = createLong(10);
      if(v1 != v2){
          printf("Long equal test1-------[FAIL] \n");
          break;
      }

      Long v3 = createLong(10);
      Long v4 = createLong(11);
      if(v3 == v4){
          printf("Long equal test2-------[FAIL] \n");
          break;
      }

      printf("Long equal test3-------[OK] \n");
      break;
  }



}
