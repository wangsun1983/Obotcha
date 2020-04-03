#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Executors.hpp"
#include "Barrier.hpp"
#include "ByteArrayReader.hpp"


using namespace obotcha;

int operatortest() {
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

      printf("ByteArray operatortest test 3-------[Success] \n");
      break;
  }
    
}
