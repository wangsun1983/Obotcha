#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "ByteArray.hpp"
#include "StrongPointer.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "Error.hpp"

using namespace obotcha;

int testByteArrayClear() {

    while(1) {
      ByteArray data = createByteArray(32);
      for(int i = 0; i < 32;i++) {
        data[i] = i;
      }

      data->quickShrink(16);
      if(data->size() != 16) {
        printf("ByteArray test Clear test 1-------[FAIL],data size is %d \n",data->size());
        break;
      }

      for(int i = 0;i < 16;i++) {
        if(data[i] != i) {
          printf("ByteArray test Clear test 2-------[FAIL] \n");
          break;
        }
      }

      data->clear();
      if(data->size() != 32) {
        printf("ByteArray test Clear test 3-------[FAIL] \n");
        break;
      }

      for(int i = 0;i<32;i++) {
        if(data[i] != 0) {
          printf("ByteArray test Clear test 4-------[FAIL] \n");
          break;
        }
      }

      printf("ByteArray test Clear test 5-------[OK] \n");
      break;
    }

    return 0;
}
