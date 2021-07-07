#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint16.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"
#include "Uint16.hpp"

using namespace obotcha;

int equaltest() {

  while(1) {
      Uint16 v1 = createUint16(10);
      Uint16 v2 = createUint16(10);
      if(v1 != v2){
          printf("Uint16 equal test1-------[FAIL] \n");
          break;
      }

      Uint16 v3 = createUint16(10);
      Uint16 v4 = createUint16(11);
      if(v3 == v4){
          printf("Uint16 equal test2-------[FAIL] \n");
          break;
      }

      printf("Uint16 equal test3-------[OK] \n");
      break;
  }



}
