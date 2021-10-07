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


void testByteArrayWriterGet() {
    while(1) {
      ByteArray array = createByteArray(8);
      ByteArrayWriter writer = createByteArrayWriter(array);
      writer->writeShort(1);
      writer->writeShort(2);

      auto arr1 = writer->getByteArray();
      if(arr1->size() != 4) {
        printf("---[TestByteArrayWriter GetArray case1] [FAILED]--- \n");
      }

      if(arr1[0] != 1 || arr1[1] != 0 || arr1[2] != 2 || arr1[3] != 0) {
        for(int i = 0;i<arr1->size();i++) {
          printf("arr1[%d] is %x \n",i,arr1[i]);
        }
        printf("---[TestByteArrayWriter GetArray case2] [FAILED]--- \n");
      }
      break;
    }

    printf("---[TestByteArrayWriter GetArray case100] [OK]--- \n");
}
