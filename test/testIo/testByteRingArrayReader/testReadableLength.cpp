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
      if(length != 5) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case1] [FAILED]---,length is %d \n",length);
        return;
      }
      printf("---[ByteRingArrayReader Test {testReadableLength} case2] [OK]--- \n");
      break;
    }

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
      if(length != 4) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case3] [FAILED]---,length is %d \n",length);
        return;
      }
      printf("---[ByteRingArrayReader Test {testReadableLength} case4] [OK]--- \n");
      break;
    }

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
      if(length != 3) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case5] [FAILED]---,length is %d \n",length);
        return;
      }
      printf("---[ByteRingArrayReader Test {testReadableLength} case6] [OK]--- \n");
      break;
    }

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
      if(length != 2) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case7] [FAILED]---,length is %d \n",length);
        return;
      }
      printf("---[ByteRingArrayReader Test {testReadableLength} case8] [OK]--- \n");
      break;
    }

    while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ringarray->push(1);
      ringarray->push(2);
      ringarray->push(3);
      ringarray->push(4);
      ringarray->push(5);

      ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
      reader->setCursor(4);
      int length = reader->getReadableLength();
      if(length != 1) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case9] [FAILED]---,length is %d \n",length);
        return;
      }
      printf("---[ByteRingArrayReader Test {testReadableLength} case10] [OK]--- \n");
      break;
    }
    
    //
    while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ringarray->push(1);
      ringarray->push(2);
      ringarray->push(3);
      ringarray->push(4);
      ringarray->push(5);

      ringarray->setEndIndex(1);
      ringarray->setSize(5);


      ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
      reader->setCursor(0);
      int length = reader->getReadableLength();
      if(length != 1) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case9] [FAILED]---,length is %d \n",length);
        return;
      }

      reader->setCursor(1);
      length = reader->getReadableLength();
      if(length != 5) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case10] [FAILED]---,length is %d \n",length);
        return;
      }

      reader->setCursor(2);
      length = reader->getReadableLength();
      if(length != 4) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case11] [FAILED]---,length is %d \n",length);
        return;
      }

      reader->setCursor(3);
      length = reader->getReadableLength();
      if(length != 3) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case12] [FAILED]---,length is %d \n",length);
        return;
      }

      reader->setCursor(4);
      length = reader->getReadableLength();
      if(length != 2) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case13] [FAILED]---,length is %d \n",length);
        return;
      }

      //
      ringarray->setEndIndex(2);
      ringarray->setSize(5);

      reader = createByteRingArrayReader(ringarray);
      reader->setCursor(0);
      length = reader->getReadableLength();
      if(length != 2) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case14] [FAILED]---,length is %d \n",length);
        return;
      }

      reader->setCursor(1);
      length = reader->getReadableLength();
      if(length != 1) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case15] [FAILED]---,length is %d \n",length);
        return;
      }

      reader->setCursor(2);
      length = reader->getReadableLength();
      if(length != 5) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case16] [FAILED]---,length is %d \n",length);
        return;
      }

      reader->setCursor(3);
      length = reader->getReadableLength();
      if(length != 4) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case17] [FAILED]---,length is %d \n",length);
        return;
      }

      reader->setCursor(4);
      length = reader->getReadableLength();
      if(length != 3) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case18] [FAILED]---,length is %d \n",length);
        return;
      }


      //
      ringarray->setEndIndex(3);
      ringarray->setSize(5);

      reader = createByteRingArrayReader(ringarray);
      reader->setCursor(0);
      length = reader->getReadableLength();
      if(length != 3) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case19] [FAILED]---,length is %d \n",length);
        return;
      }

      reader->setCursor(1);
      length = reader->getReadableLength();
      if(length != 2) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case20] [FAILED]---,length is %d \n",length);
        return;
      }

      reader->setCursor(2);
      length = reader->getReadableLength();
      if(length != 1) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case21] [FAILED]---,length is %d \n",length);
        return;
      }

      reader->setCursor(3);
      length = reader->getReadableLength();
      if(length != 5) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case22] [FAILED]---,length is %d \n",length);
        return;
      }

      reader->setCursor(4);
      length = reader->getReadableLength();
      if(length != 4) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case23] [FAILED]---,length is %d \n",length);
        return;
      }

      //
      ringarray->setEndIndex(4);
      ringarray->setSize(5);

      reader = createByteRingArrayReader(ringarray);
      reader->setCursor(0);
      length = reader->getReadableLength();
      if(length != 4) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case24] [FAILED]---,length is %d \n",length);
        return;
      }

      reader->setCursor(1);
      length = reader->getReadableLength();
      if(length != 3) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case25] [FAILED]---,length is %d \n",length);
        return;
      }

      reader->setCursor(2);
      length = reader->getReadableLength();
      if(length != 2) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case26] [FAILED]---,length is %d \n",length);
        return;
      }

      reader->setCursor(3);
      length = reader->getReadableLength();
      if(length != 1) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case27] [FAILED]---,length is %d \n",length);
        return;
      }

      reader->setCursor(4);
      length = reader->getReadableLength();
      if(length != 5) {
        printf("---[ByteRingArrayReader Test {testReadableLength} case28] [FAILED]---,length is %d \n",length);
        return;
      }

      printf("---[ByteRingArrayReader Test {testReadableLength} case100] [OK]--- \n");
      break;
    }
}
