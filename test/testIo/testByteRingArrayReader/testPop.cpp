#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"
#include "ByteRingArrayReader.hpp"
using namespace obotcha;

ByteRingArray createStartBiggerThanEnd() {
  //{7,  8,  3,  4,  5,  6}
  //         |end    |start
  ByteRingArray ringarray = createByteRingArray(6);
  ringarray->push(1);
  ringarray->push(2);
  ringarray->push(3);
  ringarray->push(4);
  ringarray->push(5);
  ringarray->push(6);

  ringarray->pop(1);
  ringarray->pop(1);


  ringarray->push(7);
  ringarray->push(8);

  ringarray->pop(1);
  ringarray->pop(1);

  return ringarray;
}

void test_pop() {
    //{1,2,3,4,5,6}
    ByteRingArray ringarray = createByteRingArray(6);
    ByteArray array = createByteArray(6);
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    array[3] = 4;
    array[4] = 5;
    array[5] = 6;

    ringarray->push(array);
    ByteRingArrayReader reader = createByteRingArrayReader(ringarray);

    byte v = 0;
    reader->readNext(v);
    reader->readNext(v);

    ByteArray poparray = reader->pop();

    if(poparray->size() != 2 ||
       poparray->at(0) != 1 ||
       poparray->at(1) != 2 ) {
        printf("---[ByteRingArrayReader Test {pop(byte val)} case0] [FAILED]---,size is %d,array[0] is %d,array[1] is %d \n",
          poparray->size(),poparray->at(0),poparray->at(1));
        return;
    }

    reader->readNext(v);
    reader->readNext(v);
    poparray = reader->pop();
    if(poparray->size() != 2 ||
       poparray->at(0) != 3 ||
       poparray->at(1) != 4 ) {
        printf("---[ByteRingArrayReader Test {pop(byte val)} case1] [FAILED]--- \n");
        return;
    }

    reader->readNext(v);

    poparray = reader->pop();
    if(poparray->size() != 1 ||
       poparray->at(0) != 5 ) {
        printf("---[ByteRingArrayReader Test {pop(byte val)} case2] [FAILED]--- \n");
        return;
    }

    poparray = reader->pop();
    if(poparray != nullptr) {
        printf("---[ByteRingArrayReader Test {pop(byte val)} case3] [FAILED]---,poparray size is %d \n",poparray->size());
        poparray->dump("--pop(byte)--");
        return;
    }

    //{7,2,3,4,5,6}
    ringarray = createByteRingArray(6);
    array = createByteArray(5);
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    array[3] = 4;
    array[4] = 5;
    ringarray->push(array);
    ringarray->pop(1);

    ByteArray array2 = createByteArray(2);
    array2[0] = 6;
    array2[1] = 7;
    ringarray->push(array2);
    int status = st(ByteRingArrayReader)::Continue;
    reader = createByteRingArrayReader(ringarray);
    byte ind = 2;
    while(1) {
        byte value = 0;
        status = reader->readNext(value);
        if(status == st(ByteRingArrayReader)::NoContent) {
          break;
        }

        if(value != ind) {
            printf("---[ByteRingArrayReader Test {pop(byte val)} case3_1] [FAILED]---,value is %d,ind is %d \n",value,ind);
            break;
        }
        ind++;
    }

    poparray = reader->pop();
    if(poparray->at(0) != 2 ||
       poparray->at(1) != 3 ||
       poparray->at(2) != 4 ||
       poparray->at(3) != 5 ||
       poparray->at(4) != 6 ||
       poparray->at(5) != 7 ) {
        printf("---[ByteRingArrayReader Test {pop(byte val)} case4] [FAILED]--- \n");
        return;
    }

    //{7,  8,  3,  4,  5,  6}
    //         |end    |start
    ringarray = createStartBiggerThanEnd();
    reader = createByteRingArrayReader(ringarray);
    status = st(ByteRingArrayReader)::Continue;

    while(status != st(ByteRingArrayReader)::NoContent) {
        byte value = 0;
        status = reader->readNext(value);
        ind++;
    }

    poparray = reader->pop();
    if(poparray->size() != 4) {
        printf("---[ByteRingArrayReader Test {pop(byte val)} case6] [FAILED]--- \n");
        return;
    }
    if(poparray->at(0) != 5 ||
       poparray->at(1) != 6 ||
       poparray->at(2) != 7 ||
       poparray->at(3) != 8 ) {
        printf("---[ByteRingArrayReader Test {pop(byte val)} case7] [FAILED]--- \n");
        return;
    }

    printf("---[ByteRingArrayReader Test {pop(byte val)} case10] [OK]--- \n");
}
