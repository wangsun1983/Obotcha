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


int basetest() {
    printf("---[ByteArrayReader Test Start]--- \n");

  /*
    for(int i = 0;i<16;i++) {
      array[i] = (byte)i;
    }
    long is 283686952306183
    short is 2057
    byte is 10
    readInt is 185339150
  */
  while(1) {
    ByteArray data = createByteArray(16);
    for(int i = 0;i<16;i++) {
       data->fill(i,i);
    }

    ByteArrayReader reader = createByteArrayReader(data);
    long v1 = reader->readLong();
    short v2 = reader->readShort();
    byte v3 = reader->readByte();
    int v4 = reader->readInt();
    if(v1 != 283686952306183 || v2 != 2057 || v3 != 10 || v4 != 185339150) {
        printf("---[TestByteArrayReader Test {readLong/readShort/readByte/readInt} case1] [FAILED]--- \n");
        break;
    }

    printf("---[TestByteArrayReader Test {readLong/readShort/readByte/readInt} case2] [Success]--- \n");
    break;
  }

  /*
    for(int i = 0;i<16;i++) {
      array[i] = (byte)(i+32);
    }
    long is 2315169217770759719
    short is 10281
    byte is 42
    readInt is 724315438
  */
  while(1) {
    ByteArray data = createByteArray(16);
    for(int i = 0;i<16;i++) {
       data->fill(i,i+32);
    }

    ByteArrayReader reader = createByteArrayReader(data);
    long v1 = reader->readLong();
    short v2 = reader->readShort();
    byte v3 = reader->readByte();
    int v4 = reader->readInt();
    if(v1 != 2315169217770759719 || v2 != 10281 || v3 != 42 || v4 != 724315438) {
        printf("---[TestByteArrayReader Test {readLong/readShort/readByte/readInt} case3] [FAILED]--- \n");
        break;
    }

    printf("---[TestByteArrayReader Test {readLong/readShort/readByte/readInt} case4] [Success]--- \n");
    break;
  }

  /*
    for(int i = 0;i<16;i++) {
      array[i] = (byte)(i+64);
    }

    long is 4630054748589213255
    short is 18505
    byte is 74
    readInt is 1263291726
  */
  while(1) {
    ByteArray data = createByteArray(16);
    for(int i = 0;i<16;i++) {
       data->fill(i,i+64);
    }

    ByteArrayReader reader = createByteArrayReader(data);
    long v1 = reader->readLong();
    short v2 = reader->readShort();
    byte v3 = reader->readByte();
    int v4 = reader->readInt();
    if(v1 != 4630054748589213255 || v2 != 18505 || v3 != 74 || v4 != 1263291726) {
        printf("---[TestByteArrayReader Test {readLong/readShort/readByte/readInt} case5] [FAILED]--- \n");
        break;
    }

    printf("---[TestByteArrayReader Test {readLong/readShort/readByte/readInt} case6] [Success]--- \n");
    break;
  }

  //int readByteArray(ByteArray);
  while(1) {
    ByteArray data = createByteArray(16);
    for(int i = 0;i<16;i++) {
       data->fill(i,i+64);
    }

    ByteArrayReader reader = createByteArrayReader(data);
    ByteArray readarray = createByteArray(64);
    int len = reader->readByteArray(readarray);
    if(len != 16) {
        printf("---[TestByteArrayReader Test {readByteArray} case1] [FAILED]--- \n");
        break;
    }

    for(int j = 0;j<16;j++) {
        if(readarray->at(j) != data->at(j)) {
            printf("---[TestByteArrayReader Test {readByteArray} case2] [FAILED]--- \n");
            break;
        }
    }

    printf("---[TestByteArrayReader Test {readByteArray} case3] [Success]--- \n");
    break;
  }
}
