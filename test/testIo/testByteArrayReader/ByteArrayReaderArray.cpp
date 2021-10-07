#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Barrier.hpp"
#include "ByteArrayReader.hpp"
#include <string.h>

using namespace obotcha;


void testReaderArray() {
    byte array[] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
    while(1) {
      ByteArray testData = createByteArray(array,8);
      ByteArrayReader reader = createByteArrayReader(testData);

      //2 byte
      ByteArray d1 = createByteArray(2);
      reader->readByteArray(d1);
      if(d1[0] != 0x01 ||d1[1] != 0x02) {
        printf("---[TestByteArrayReader Read Array case1] [FAILED]--- \n");
        break;
      }

      //4 byte
      ByteArray d2 = createByteArray(4);
      reader->readByteArray(d2);
      if(d2[0] != 0x03 ||d2[1] != 0x04 ||d2[2] != 0x05 || d2[3] != 0x06) {
        printf("---[TestByteArrayReader Read Array case2] [FAILED]--- \n");
        break;
      }

      //2 byte
      ByteArray d3 = createByteArray(2);
      reader->readByteArray(d3);
      if(d3[0] != 0x07 ||d3[1] != 0x08) {
        printf("---[TestByteArrayReader Read Array case3] [FAILED]--- \n");
        break;
      }
      break;
    }

    while(1) {
      ByteArray testData = createByteArray(array,8);
      ByteArrayReader reader = createByteArrayReader(testData);

      //2 byte
      ByteArray d1 = createByteArray(2);
      reader->readByteArray(d1);
      if(d1[0] != 0x01 ||d1[1] != 0x02) {
        printf("---[TestByteArrayReader Read Array case4] [FAILED]--- \n");
        break;
      }

      ByteArray d2 = createByteArray(16);
      int len = reader->readByteArray(d2);
      if(len != 6) {
        printf("---[TestByteArrayReader Read Array case5] [FAILED]--- \n");
        break;
      }

      for(int i = 0;i < len;i++) {
        if(d2[i] != array[i+2]) {
          printf("---[TestByteArrayReader Read Array case6] [FAILED]--- d1[%d] is %d,array[%d] is %d \n",i,d1[i],i+2,array[i+2]);
        }
      }
      break;
    }

    printf("---[TestByteArrayReader Read Array case100] [OK]--- \n");
}
