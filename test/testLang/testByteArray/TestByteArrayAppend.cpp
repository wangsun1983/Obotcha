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

int testappend() {

    //testAppend
    while(1) {
      //case1
      ByteArray data1 = createByteArray(16);
      for(int i = 0;i<16;i++) {
        data1[i] = i;
      }

      ByteArray data2 = createByteArray(16);
      for(int i = 0;i<16;i++) {
        data2[i] = i+16;
      }

      data1->append(data2);
      if(data1->size() != 32) {
        printf("ByteArray testappend test 1-------[FAIL] \n");
        break;
      }

      for(int i = 0;i<32;i++) {
        if(data1[i] != i) {
            printf("ByteArray testappend test 2-------[FAIL] \n");
            break;
        }
      }
      

      //case2
      ByteArray data3 = createByteArray(8);
      for(int i = 0;i<8;i++) {
        data3[i] = i;
      }

      byte data4[12];
      if(data3->append(data4,-1) != -InvalidParam) {
        printf("ByteArray testappend test 3-------[FAIL] \n");
        break;
      }

      printf("ByteArray testappend test 4-------[Success] \n");
      break;
    }
}
