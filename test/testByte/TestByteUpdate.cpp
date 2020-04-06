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


int updatetest() {
  while(1) {
      //case 1
      Byte v1 = createByte(10);
      v1->update(2);

      if(v1->toValue() != 2){
          printf("Byte update special test1-------[FAIL] \n");
          break;
      }

      //case 2
      Byte v2 = createByte(10);
      Byte v2_1 = createByte(2);
      v2->update(v2_1);

      if(v2->toValue() != 2) {
          printf("Byte update special test2-------[FAIL] \n");
          break;
      }

      //case 3
      Byte v3;
      try {
        v1->update(v3);
        printf("Byte update special test3-------[FAIL] \n");
      }catch(NullPointerException e) {}

      printf("yte update special test4-------[OK] \n");
      break;
  }



}
