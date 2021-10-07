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


void testByteArrayWriterString() {
    while(1) {
      ByteArray d1 = createByteArray(16);
      ByteArrayWriter writer = createByteArrayWriter(d1);
      char array[] = {'h','e','l','l','o','\0'};
      writer->writeString((const char *)array);

      if(!d1->toString()->equals("hello")) {
        printf("---[TestByteArrayWriter Write String case1] [FAILED]--- \n");
      }
      break;
    }

    while(1) {
      ByteArray d1 = createByteArray(16);
      ByteArrayWriter writer = createByteArrayWriter(d1);
      String array = createString("hello");
      writer->writeString(array);

      if(!d1->toString()->equals("hello")) {
        printf("---[TestByteArrayWriter Write String case2] [FAILED]--- \n");
      }
      break;
    }

    printf("---[TestByteArrayWriter Write String case100] [OK]--- \n");
}
