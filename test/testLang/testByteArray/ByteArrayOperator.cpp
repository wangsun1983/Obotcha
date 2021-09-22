#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Barrier.hpp"
#include "ByteArrayReader.hpp"

using namespace obotcha;

void operatortest() {
  //
  while(1) {

      //case1
      ByteArray array = createByteArray(5);
      array[0] = 0;
      array[1] = 1;
      array[2] = 2;
      array[3] = 3;
      array[4] = 4;

      if(array->at(0) != 0
        ||array->at(1) != 1
        ||array->at(2) != 2
        ||array->at(3) != 3
        ||array->at(4) != 4){
        printf("ByteArray operatortest test 1-------[FAIL] \n");
        break;
      }

      //case2
      ByteArray array2 = createByteArray(5);
      try {
        array2[100] = 1;
        printf("ByteArray operatortest test 2-------[FAIL] \n");
      } catch(ArrayIndexOutOfBoundsException e) {}

      //case 3
      ByteArray array3 = createByteArray(128);
      for(int i = 0;i<128;i++) {
        array3[i] = i+1;
      }

      for(int j = 0;j<128;j++) {
        //printf("array3[%d] is %d \n",j,array3[j]);
        if(array3[j] != j+1) {
          printf("ByteArray operatortest test 3-------[FAIL] \n");
          return;
        }
      }

      printf("ByteArray operatortest test 3-------[OK] \n");
      break;
  }

  //-1 index
  while(1) {
    ByteArray arr1 = createByteArray(16);
    for(int i = 0;i<16;i++) {
      arr1[i] = i;
    }

    bool isException = false;
    try {
      arr1[-1] = 3;
    }catch(ArrayIndexOutOfBoundsException e) {
      isException = true;
    }

    if(!isException) {
      printf("ByteArray operatortest test 5-------[OK] \n");
    }
    printf("ByteArray operatortest test 6-------[OK] \n");
    break;
  }

}
