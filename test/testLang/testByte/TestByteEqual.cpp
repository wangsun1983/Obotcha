#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Byte.hpp"
#include "StrongPointer.hpp"
#include "InitializeException.hpp"
#include "Byte.hpp"

using namespace obotcha;

void equaltest() {

  while(1) {
      Byte v1 = createByte(10);
      Byte v2 = createByte(10);
      if(v1 != v2){
          printf("Byte equal test1-------[FAIL] \n");
          break;
      }

      Byte v3 = createByte(10);
      Byte v4 = createByte(11);
      if(v3 == v4){
          printf("Byte equal test2-------[FAIL] \n");
          break;
      }

      printf("Byte equal test3-------[OK] \n");
      break;
  }



}
