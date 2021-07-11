#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"
#include "ByteRingArrayReader.hpp"
using namespace obotcha;


void testPopAll() {

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
      ByteArray arr = reader->pop();
      if(arr != nullptr) {
        printf("---[ByteRingArrayReader Test {testPopAll} case1] [FAILED]--- \n");
        return;
      }
      printf("---[ByteRingArrayReader Test {testPopAll} case1] [OK]--- \n");
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
      ByteArray arr = reader->pop();
      if(arr != nullptr) {
        printf("---[ByteRingArrayReader Test {testPopAll} case3] [FAILED]--- \n");
        return;
      }

      printf("---[ByteRingArrayReader Test {testPopAll} case5] [OK]--- \n");
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

      ByteArray arr = reader->pop();
      if(arr->size() != 1) {
        printf("---[ByteRingArrayReader Test {testPopAll} case6] [FAILED]--- \n");
        return;
      }

      if(arr[0] != 1) {
        printf("---[ByteRingArrayReader Test {testPopAll} case7] [FAILED]--- \n");
        return;
      }

      printf("---[ByteRingArrayReader Test {testPopAll} case8] [OK]--- \n");
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

      ByteArray arr = reader->pop();
      if(arr->size() != 2) {
        printf("---[ByteRingArrayReader Test {testPopAll} case9] [FAILED]--- \n");
        return;
      }

      if(arr[0] != 1 || arr[1] != 2) {
        printf("---[ByteRingArrayReader Test {testPopAll} case10] [FAILED]--- \n");
        return;
      }

      printf("---[ByteRingArrayReader Test {testPopAll} case11] [OK]--- \n");
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

      ByteArray arr = reader->pop();
      if(arr->size() != 3) {
        printf("---[ByteRingArrayReader Test {testPopAll} case10] [FAILED]--- \n");
        return;
      }

      if(arr[0] != 1 || arr[1] != 2 || arr[2] != 3) {
        printf("---[ByteRingArrayReader Test {testPopAll} case11] [FAILED]--- \n");
        return;
      }

      printf("---[ByteRingArrayReader Test {testPopAll} case12] [OK]--- \n");
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

      ByteArray arr = reader->pop();
      if(arr->size() != 1) {
        printf("---[ByteRingArrayReader Test {testPopAll} case13] [FAILED]--- \n");
        return;
      }

      if(arr[0] != 5) {
        printf("---[ByteRingArrayReader Test {testPopAll} case14] [FAILED]--- \n");
        return;
      }

      printf("---[ByteRingArrayReader Test {testPopAll} case15] [OK]--- \n");
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

      ByteArray arr = reader->pop();
      if(arr->size() != 2) {
        printf("---[ByteRingArrayReader Test {testPopAll} case16] [FAILED]--- \n");
        return;
      }

      if(arr[0] != 5 || arr[1] != 1) {
        printf("---[ByteRingArrayReader Test {testPopAll} case17] [FAILED]--- \n");
        return;
      }

      printf("---[ByteRingArrayReader Test {testPopAll} case18] [OK]--- \n");
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

      ByteArray arr = reader->pop();
      if(arr->size() != 3) {
        printf("---[ByteRingArrayReader Test {testPopAll} case19] [FAILED]--- \n");
        return;
      }

      if(arr[0] != 5 || arr[1] != 1 || arr[2] != 2) {
        printf("---[ByteRingArrayReader Test {testPopAll} case20] [FAILED]--- \n");
        return;
      }

      printf("---[ByteRingArrayReader Test {testPopAll} case21] [OK]--- \n");
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

      ByteArray arr = reader->pop();
      if(arr->size() != 4) {
        printf("---[ByteRingArrayReader Test {testPopAll} case22] [FAILED]--- \n");
        return;
      }

      if(arr[0] != 5 || arr[1] != 1 || arr[2] != 2 || arr[3] != 3) {
        printf("---[ByteRingArrayReader Test {testPopAll} case23] [FAILED]--- \n");
        return;
      }

      byte value = 0;
      if(reader->readNext(value) != ByteRingArrayReadComplete) {
        printf("---[ByteRingArrayReader Test {testPopAll} case24] [FAILED]--- \n");
        return;
      }

      printf("---[ByteRingArrayReader Test {testPopAll} case25] [OK]--- \n");
      break;
    }

}
