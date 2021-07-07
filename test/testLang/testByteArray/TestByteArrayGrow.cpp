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

int testgrow() {

    //test growTo
    while(1) {
      //case1
      ByteArray arr = createByteArray(8);
      for(int i = 0;i<8;i++) {
        arr[i] = i;
      }

      arr->growTo(16);
      if(arr->size() != 16) {
        printf("ByteArray testgrow test 1-------[FAIL] \n");
        break;
      }

      for(int i = 0;i<8;i++) {
        if(arr[i] != i) {
          printf("ByteArray testgrow test 2-------[FAIL] \n");
          break;
        }
      }

      //case2
      ByteArray arr2 = createByteArray(8);
      if(arr2->growTo(2) != -InvalidParam) {
        printf("ByteArray testgrow test 3-------[FAIL] \n");
        break;
      }

      printf("ByteArray testgrow test 4-------[Success] \n");
      break;
    }

    //test growBy
    while(1) {
      //case1
      ByteArray arr = createByteArray(8);
      for(int i = 0;i<8;i++) {
        arr[i] = i;
      }

      arr->growBy(16);
      if(arr->size() != 24) {
        printf("ByteArray testgrow test 5-------[FAIL] \n");
        break;
      }

      for(int i = 0;i<8;i++) {
        if(arr[i] != i) {
          printf("ByteArray testgrow test 6-------[FAIL] \n");
          break;
        }
      }

      printf("ByteArray testgrow test 7-------[Success] \n");
      break;
    }

}
