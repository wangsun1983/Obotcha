#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <fcntl.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "ByteArray.hpp"
#include "StrongPointer.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"

using namespace obotcha;


void dumptest() {

    while(1) {
      //case1
      ByteArray arr1 = createByteArray(16);
      for(int i = 0;i<16;i++) {
        arr1[i] = i;
      }

      arr1->dumpToFile("case1.data");

      int fd = open("case1.data",O_RDONLY);
      char buff[256];
      int ret = read(fd,buff,256);
      if(ret != 16) {
        printf("ByteArray dump test 1-------[FAIL] \n");
        break;
      }

      for(int i = 0;i<16;i++) {
        if(arr1[i]!= buff[i]) {
          printf("ByteArray dump test 2-------[FAIL] \n");
          break;
        }
      }

      printf("ByteArray dump test 3-------[OK] \n");
      break;
    }

}
