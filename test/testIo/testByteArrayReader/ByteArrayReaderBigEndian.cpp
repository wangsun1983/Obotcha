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


void testByteArrayBigEndian() {
    byte array[] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
    while(1) {
      ByteArray testData = createByteArray(array,8);
      ByteArrayReader reader = createByteArrayReader(testData,Global::BigEndian);

      //test short
      short int v1 = 0;
      v1 = (array[0]<<8)|array[1];
      int v1_chk = reader->readShort();
      if(v1 != v1_chk) {
        printf("---[TestByteArrayReader BigEndian case1] [FAILED]---,v1 is %d,v1_chk is %d \n",v1,v1_chk);
      }

      short int v2 = 0;
      v2 = (array[2]<<8)|array[3];
      int v2_chk = reader->readShort();
      if(v2 != v2_chk) {
        printf("---[TestByteArrayReader BigEndian case2] [FAILED]---,v2 is %d,v2_chk is %d \n",v2,v2_chk);
      }

      short int v3 = 0;
      v3 = (array[4]<<8)|array[5];
      int v3_chk = reader->readShort();
      if(v3 != v3_chk) {
        printf("---[TestByteArrayReader BigEndian case3] [FAILED]---,v3 is %d,v3_chk is %d \n",v3,v3_chk);
      }

      short int v4 = 0;
      v4 = (array[6]<<8)|array[7];
      int v4_chk = reader->readShort();
      if(v4 != v4_chk) {
        printf("---[TestByteArrayReader BigEndian case4] [FAILED]---,v4 is %d,v4_chk is %d \n",v4,v4_chk);
      }
      break;
    }

    while(1) {
      ByteArray testData = createByteArray(array,8);
      ByteArrayReader reader = createByteArrayReader(testData,Global::BigEndian);
      int v1 = 0;
      v1 = (array[0]<<24)|(array[1]<<16)|(array[2]<<8)|(array[3]);
      int v1_chk = reader->readInt();
      if(v1 != v1_chk) {
        printf("---[TestByteArrayReader BigEndian case5] [FAILED]---,v1 is %d,v1_chk is %d \n",v1,v1_chk);
      }

      int v2 = 0;
      v2 = (array[4]<<24)|(array[5]<<16)|(array[6]<<8)|(array[7]);
      int v2_chk = reader->readInt();
      if(v2 != v2_chk) {
        printf("---[TestByteArrayReader BigEndian case6] [FAILED]---,v2 is %d,v2_chk is %d \n",v2,v2_chk);
      }
      break;
    }

    while(1) {
      ByteArray testData = createByteArray(array,8);
      ByteArrayReader reader = createByteArrayReader(testData,Global::BigEndian);
      long v1 = 0;
      v1 = (long)array[7]|((long)array[6]<<8)|((long)array[5]<<16)|((long)array[4]<<24)|((long)array[3]<<32)|((long)array[2]<<40)|((long)array[1]<<48)|((long)array[0]<<56);
      long v1_chk = reader->readLong();
      if(v1 != v1_chk) {
        printf("---[TestByteArrayReader BigEndian case7] [FAILED]---,v1 is %lx,v1_chk is %lx \n",v1,v1_chk);
      }

      break;
    }

    while(1) {
      ByteArray testData = createByteArray(array,8);
      ByteArrayReader reader = createByteArrayReader(testData,Global::BigEndian);

      for(int i = 0;i<8;i++) {
        byte v = reader->readByte();
        if(v != array[i]) {
          printf("---[TestByteArrayReader BigEndian case8] [FAILED]---,v is %d,array[%d] is %d \n",v,i,array[i]);
        }
      }
      break;
    }

    printf("---[TestByteArrayReader BigEndian case8] [OK]--- \n");
}
