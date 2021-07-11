#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"
#include "ByteRingArrayReader.hpp"
using namespace obotcha;


void testReadableLength() {

    //case1
    //data:[1(start/end/cursor),2,3,4,5]
    while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ringarray->push(1);
      ringarray->push(2);
      ringarray->push(3);
      ringarray->push(4);
      ringarray->push(5);

      ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
      reader->setCursor(0);
      int length = reader->getReadableLength();
      if(length != 0) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case1] [FAILED]---,length is %d \n",length);
        return;
      }
      printf("---[ByteRingArrayReader Test {testReadableLength} case1] [OK]--- \n");
      break;
    }

    //case2
    //data:[1(start/cursor),2,3,4,5(end)]
    while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ringarray->push(1);
      ringarray->push(2);
      ringarray->push(3);
      ringarray->push(4);
      ringarray->push(5);
      ringarray->setStartIndex(0);
      ringarray->setEndIndex(4);

      ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
      reader->setCursor(0);
      int length = reader->getReadableLength();
      if(length != 0) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case2] [FAILED]--- \n");
        return;
      }
      printf("---[ByteRingArrayReader Test {testReadableLength} case2] [OK]--- \n");
      break;

    }

    //case3
    //data:[1(start),2(cursor),3,4,5(end)]
    while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ringarray->push(1);
      ringarray->push(2);
      ringarray->push(3);
      ringarray->push(4);
      ringarray->push(5);

      ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
      reader->setCursor(1);

      int length = reader->getReadableLength();
      if(length != 1) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case3] [FAILED]--- \n");
        return;
      }
      printf("---[ByteRingArrayReader Test {testReadableLength} case3] [OK]--- \n");
      break;
    }

    //case4
    //data:[1(start),2,3(cursor),4,5(end)]
    while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ringarray->push(1);
      ringarray->push(2);
      ringarray->push(3);
      ringarray->push(4);
      ringarray->push(5);

      ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
      reader->setCursor(2);

      int length = reader->getReadableLength();
      if(length != 2) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case4] [FAILED]--- \n");
        return;
      }
      printf("---[ByteRingArrayReader Test {testReadableLength} case4] [OK]--- \n");
      break;
    }

    //case5
    //data:[1(start),2,3,4(cursor),5(end)]
    while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ringarray->push(1);
      ringarray->push(2);
      ringarray->push(3);
      ringarray->push(4);
      ringarray->push(5);

      ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
      reader->setCursor(3);

      int length = reader->getReadableLength();
      if(length != 3) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case5] [FAILED]--- \n");
        return;
      }
      printf("---[ByteRingArrayReader Test {testReadableLength} case5] [OK]--- \n");
      break;
    }

    //case6
    //data:[1(cursor),2,3,4(end),5(start)]
    while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ringarray->push(1);
      ringarray->push(2);
      ringarray->push(3);
      ringarray->push(4);
      ringarray->push(5);
      ringarray->setStartIndex(4);
      ringarray->setEndIndex(3);

      ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
      reader->setCursor(0);

      int length = reader->getReadableLength();
      if(length != 1) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case6] [FAILED]--- \n");
        return;
      }
      printf("---[ByteRingArrayReader Test {testReadableLength} case6] [OK]--- \n");
      break;
    }

    //case7
    //data:[1,2(cursor),3,4(end),5(start)]
    while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ringarray->push(1);
      ringarray->push(2);
      ringarray->push(3);
      ringarray->push(4);
      ringarray->push(5);
      ringarray->setStartIndex(4);
      ringarray->setEndIndex(3);

      ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
      reader->setCursor(1);

      int length = reader->getReadableLength();
      if(length != 2) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case7] [FAILED]--- \n");
        return;
      }
      printf("---[ByteRingArrayReader Test {testReadableLength} case7] [OK]--- \n");
      break;
    }

    //case8
    //data:[1,2,3(cursor),4(end),5(start)]
    while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ringarray->push(1);
      ringarray->push(2);
      ringarray->push(3);
      ringarray->push(4);
      ringarray->push(5);
      ringarray->setStartIndex(4);
      ringarray->setEndIndex(3);

      ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
      reader->setCursor(2);

      int length = reader->getReadableLength();
      if(length != 3) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case8] [FAILED]--- \n");
        return;
      }
      printf("---[ByteRingArrayReader Test {testReadableLength} case8] [OK]--- \n");
      break;
    }

    //case9
    //data:[1,2,3,4(end/cursor),5(start)]
    while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ringarray->push(1);
      ringarray->push(2);
      ringarray->push(3);
      ringarray->push(4);
      ringarray->push(5);
      ringarray->setStartIndex(4);
      ringarray->setEndIndex(3);

      ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
      reader->setCursor(3);

      int length = reader->getReadableLength();
      if(length != 4) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case9] [FAILED]--- \n");
        return;
      }
      printf("---[ByteRingArrayReader Test {testReadableLength} case9] [OK]--- \n");
      break;
    }

}
