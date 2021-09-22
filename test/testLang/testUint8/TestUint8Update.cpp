#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "ByteArray.hpp"
#include "StrongPointer.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "IllegalArgumentException.hpp"
#include "NullPointerException.hpp"

using namespace obotcha;

void updatetest() {
  while(1) {
      //case 1
      Uint8 v1 = createUint8(10);
      v1->update(2);

      if(v1->toValue() != 2){
          printf("Uint8 update special test1-------[FAIL] \n");
          break;
      }

      //case 2
      Uint8 v2 = createUint8(10);
      Uint8 v2_1 = createUint8(2);
      v2->update(v2_1);

      if(v2->toValue() != 2) {
          printf("Uint8 update special test2-------[FAIL] \n");
          break;
      }

      printf("yte update special test4-------[OK] \n");
      break;
  }
}
