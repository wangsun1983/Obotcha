#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint8.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"
#include "Uint8.hpp"

using namespace obotcha;

int equaltest() {

  while(1) {
      Uint8 v1 = createUint8(10);
      Uint8 v2 = createUint8(10);
      if(v1 != v2){
          printf("Uint8 equal test1-------[FAIL] \n");
          break;
      }

      Uint8 v3 = createUint8(10);
      Uint8 v4 = createUint8(11);
      if(v3 == v4){
          printf("Uint8 equal test2-------[FAIL] \n");
          break;
      }

      printf("Uint8 equal test3-------[OK] \n");
      break;
  }



}
