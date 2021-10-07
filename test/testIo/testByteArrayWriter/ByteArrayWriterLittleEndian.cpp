#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Barrier.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"
#include <string.h>

using namespace obotcha;


void testByteArrayLittleEndian() {
    while(1) {
      ByteArray data = createByteArray(8);
      ByteArrayWriter writer = createByteArrayWriter(data);
      writer->writeShort(1);
      writer->writeShort(2);
      writer->writeShort(3);
      writer->writeShort(4);
      byte *d1 = data->toValue();

      short int v1 = d1[0] | d1[1]<<8;
      if(v1 != 1) {
        printf("---[TestByteArrayWriter LittleEndia case1] [FAILED]---v1 is %d \n",v1);
      }

      writer->reset();
      writer->writeInt(12);
      writer->writeInt(198);
      //for(int i = 0;i<8;i++) {
      //  printf("d[%d] is %x \n",i,d1[i]);
      //}
      int v2 = d1[0] | d1[1]<<8 |d1[2]<<16 |d1[3]<<24;
      if(v2 != 12) {
        printf("---[TestByteArrayWriter LittleEndia case2] [FAILED]--- \n");
      }

      int v3 = d1[4] | d1[5]<<8 |d1[6]<<16 |d1[7]<<24;
      if(v3 != 198) {
        printf("---[TestByteArrayWriter LittleEndia case3] [FAILED]---,v3 is %d \n",v3);
      }

      writer->reset();
      writer->writeLong(12345678);
      long v4 =  (long)d1[0] | (long)d1[1]<<8 |(long)d1[2]<<16 |(long)d1[3]<<24|(long)d1[4]<<32
                |(long)d1[5]<<40|(long)d1[6]<<48|(long)d1[7]<<56;
      if(v4 != 12345678) {
        printf("---[TestByteArrayWriter LittleEndia case4] [FAILED]--- \n");
      }

      writer->reset();
      writer->writeByte(1);
      writer->writeByte(2);
      writer->writeByte(3);
      writer->writeByte(4);
      writer->writeByte(5);
      writer->writeByte(6);
      writer->writeByte(7);
      writer->writeByte(8);
      for(int i = 0;i<8;i++) {
        if(d1[i] != i + 1) {
          printf("---[TestByteArrayWriter LittleEndia case5] [FAILED]---,d1[%d] is %d\n",i,d1[i]);
        }
      }
      break;
    }

    while(1) {
      ByteArray data = createByteArray(8);
      ByteArrayWriter writer = createByteArrayWriter(data);

      byte testData[8] = {0};
      long val = 12345678;
      writer->writeLong(val);
      memcpy(testData,&val,sizeof(long));
      for(int i = 0;i<8;i++) {
        if(testData[i] != data[i]) {
          printf("---[TestByteArrayWriter LittleEndia case6] [FAILED]---,testdata[%d] is %x,data[%d] is %x\n",i,testData[i],i,data[i]);
          break;
        }
      }
      break;
    }

    while(1) {
      ByteArray data = createByteArray(8);
      ByteArrayWriter writer = createByteArrayWriter(data);

      byte testData[8] = {0};
      int val1 = 1234;
      int val2 = 4567;
      writer->writeInt(val1);
      writer->writeInt(val2);

      memcpy(testData,&val1,sizeof(int));
      memcpy(testData + 4,&val2,sizeof(int));
      for(int i = 0;i<8;i++) {
        if(testData[i] != data[i]) {
          printf("---[TestByteArrayWriter LittleEndia case7] [FAILED]---,testdata[%d] is %x,data[%d] is %x\n",i,testData[i],i,data[i]);
          break;
        }
      }
      break;
    }

    printf("---[TestByteArrayWriter LittleEndia case100] [OK]--- \n");
}
