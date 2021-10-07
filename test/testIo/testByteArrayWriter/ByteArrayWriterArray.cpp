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


void testByteArrayWriterArray() {
    while(1) {
      ByteArray array = createByteArray(8);
      byte arr1[] = {1,2,3,4};
      byte arr2[] = {5,6,7,8};

      ByteArrayWriter writer = createByteArrayWriter(array);
      writer->writeByteArray(createByteArray((const byte *)arr1,4));
      writer->writeByteArray(createByteArray((const byte *)arr2,4));

      for(int i = 0;i<8;i++) {
        if(array[i] != i + 1) {
          printf("---[TestByteArrayWriter Write Array case1] [FAILED]--- \n");
        }
      }

      break;
    }

    while(1) {
      ByteArray d1 = createByteArray(16);
      ByteArrayWriter writer = createByteArrayWriter(d1);

      byte data[] = {1,2,3,4,5,6};
      ByteArray d2 = createByteArray((const byte *)data,6);
      writer->writeByteArray(d2,2,3);
      if(d1[0] != 3 || d1[1] != 4 || d1[2] != 5) {
        printf("---[TestByteArrayWriter Write Array case2] [FAILED]--- \n");
      }
      break;
    }

    while(1) {
      ByteArray d1 = createByteArray(16);
      ByteArrayWriter writer = createByteArrayWriter(d1);

      byte data[] = {1,2,3,4,5,6};
      writer->write(data+1,3);
      if(d1[0] != 2 || d1[1] != 3 || d1[2] != 4) {
        printf("---[TestByteArrayWriter Write Array case3] [FAILED]--- \n");
      }
      break;
    }

    printf("---[TestByteArrayWriter Write Array case100] [OK]--- \n");
}
