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


void testByteArrayLittleEndian() {
    byte array[] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
    while(1) {
      ByteArray testData = createByteArray(array,8);

      ByteArrayReader reader = createByteArrayReader(testData,Global::LittleEndian);

      //test short
      short int v1 = 0;
      v1 = array[0]|(array[1]<<8);
      int v1_chk = reader->readShort();
      if(v1 != v1_chk) {
        printf("---[TestByteArrayReader LittleEndia case1] [FAILED]---,v1 is %d,v1_chk is %d \n",v1,v1_chk);
      }

      short int v2 = 0;
      v2 = array[2]|(array[3]<<8);
      int v2_chk = reader->readShort();
      if(v2 != v2_chk) {
        printf("---[TestByteArrayReader LittleEndia case2] [FAILED]---,v2 is %d,v2_chk is %d \n",v2,v2_chk);
      }

      short int v3 = 0;
      v3 = array[4]|(array[5]<<8);
      int v3_chk = reader->readShort();
      if(v3 != v3_chk) {
        printf("---[TestByteArrayReader LittleEndia case3] [FAILED]---,v3 is %d,v3_chk is %d \n",v3,v3_chk);
      }

      short int v4 = 0;
      v4 = array[6]|(array[7]<<8);
      int v4_chk = reader->readShort();
      if(v4 != v4_chk) {
        printf("---[TestByteArrayReader LittleEndia case4] [FAILED]---,v4 is %d,v4_chk is %d \n",v4,v4_chk);
      }
      break;
    }

    while(1) {
      ByteArray testData = createByteArray(array,8);
      ByteArrayReader reader = createByteArrayReader(testData,Global::LittleEndian);
      int v1 = 0;
      v1 = array[0]|(array[1]<<8)|(array[2]<<16)|(array[3]<<24);
      int v1_chk = reader->readInt();
      if(v1 != v1_chk) {
        printf("---[TestByteArrayReader LittleEndia case5] [FAILED]---,v1 is %d,v1_chk is %d \n",v1,v1_chk);
      }

      int v2 = 0;
      v2 = array[4]|(array[5]<<8)|(array[6]<<16)|(array[7]<<24);
      int v2_chk = reader->readInt();
      if(v2 != v2_chk) {
        printf("---[TestByteArrayReader LittleEndia case6] [FAILED]---,v2 is %d,v2_chk is %d \n",v2,v2_chk);
      }
      break;
    }

    while(1) {
      ByteArray testData = createByteArray(array,8);
      ByteArrayReader reader = createByteArrayReader(testData,Global::LittleEndian);
      long v1 = 0;
      v1 = (long)array[0]|((long)array[1]<<8)|((long)array[2]<<16)|((long)array[3]<<24)|((long)array[4]<<32)|((long)array[5]<<40)|((long)array[6]<<48)|((long)array[7]<<56);
      long v1_chk = reader->readLong();
      if(v1 != v1_chk) {
        printf("---[TestByteArrayReader LittleEndia case7] [FAILED]---,v1 is %lx,v1_chk is %lx \n",v1,v1_chk);
      }

      break;
    }

    while(1) {
      ByteArray testData = createByteArray(array,8);
      ByteArrayReader reader = createByteArrayReader(testData,Global::LittleEndian);

      for(int i = 0;i<8;i++) {
        byte v = reader->readByte();
        if(v != array[i]) {
          printf("---[TestByteArrayReader LittleEndia case8] [FAILED]---,v is %d,array[%d] is %d \n",v,i,array[i]);
        }
      }
      break;
    }

    printf("---[TestByteArrayReader LittleEndia case8] [OK]--- \n");
}
