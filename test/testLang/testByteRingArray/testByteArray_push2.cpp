#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"

using namespace obotcha;

int testByteRingArrayPush2() {

  //case1 overflow test
  //data:[1(start),2,3,4,5(end)]
  while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ByteArray data = createByteArray(6);
      data[0] = 0;
      data[1] = 1;
      data[2] = 2;
      data[3] = 3;
      data[4] = 4;
      data[5] = 5;
      bool isException = false;
      try {
        ringarray->push(data);
      }catch(Exception e) {
        isException = true;
      }

      if(!isException) {
        printf("---[ByteRingArray Test push_test {push_test1} case1] [FAILED]--- \n");
        return 0;
      }

      printf("---[ByteRingArray Test push_test {push_test1} case1] [OK]--- \n");
      break;
  }

  //case2 full test
  //data:[1,2(start),3,4,5(end)]
  while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ringarray->push(0);
      ringarray->push(1);
      ringarray->push(2);
      ringarray->push(3);
      ringarray->push(4);

      ByteArray data = createByteArray(3);
      data[0] = 0;
      data[1] = 1;
      data[2] = 2;
      bool isException = false;
      try {
        ringarray->push(data);
      }catch(Exception e) {
        isException = true;
      }

      if(!isException) {
        printf("---[ByteRingArray Test push_test {push_test2} case1] [FAILED]--- \n");
        return 0;
      }

      printf("---[ByteRingArray Test push_test {push_test2} case1] [OK]--- \n");
      break;
  }

  //case3
  //data:[1,2(start),3,4,5(end)]
  while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ringarray->push(1);
      ringarray->push(2);
      ringarray->push(3);
      ringarray->push(4);
      ringarray->push(5);
      ringarray->setStartIndex(1);
      ringarray->setEndIndex(4);
      ringarray->setStatus(st(ByteRingArray)::Partial);

      ByteArray data = createByteArray(2);
      data[0] = 10;
      data[1] = 11;
      //[11,2,3,4,10]
      ringarray->push(data);

      if(ringarray->at(0) != 11 || ringarray->at(1) != 2
        ||ringarray->at(2) != 3 || ringarray->at(3) != 4
        ||ringarray->at(4) != 10) {
        printf("ring[0] is %d \n",ringarray->at(0));
        printf("ring[1] is %d \n",ringarray->at(1));
        printf("ring[2] is %d \n",ringarray->at(2));
        printf("ring[3] is %d \n",ringarray->at(3));
        printf("ring[4] is %d \n",ringarray->at(4));
        printf("---[ByteRingArray Test push_test {push_test3} case1] [FAILED]--- \n");
        return 0;
      }

      printf("---[ByteRingArray Test push_test {push_test3} case1] [OK]--- \n");
      break;
  }

  //case3
  //data:[1,2,3(start),4,5(end)]
  while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ringarray->push(1);
      ringarray->push(2);
      ringarray->push(3);
      ringarray->push(4);
      ringarray->push(5);
      ringarray->setStartIndex(2);
      ringarray->setEndIndex(4);
      ringarray->setStatus(st(ByteRingArray)::Partial);

      ByteArray data = createByteArray(3);
      data[0] = 10;
      data[1] = 11;
      data[2] = 12;
      //[11,12,3,4,10]
      ringarray->push(data);

      if(ringarray->at(0) != 11 || ringarray->at(1) != 12
        ||ringarray->at(2) != 3 || ringarray->at(3) != 4
        ||ringarray->at(4) != 10) {
        printf("ring[0] is %d \n",ringarray->at(0));
        printf("ring[1] is %d \n",ringarray->at(1));
        printf("ring[2] is %d \n",ringarray->at(2));
        printf("ring[3] is %d \n",ringarray->at(3));
        printf("ring[4] is %d \n",ringarray->at(4));
        printf("---[ByteRingArray Test push_test {push_test4} case1] [FAILED]--- \n");
        return 0;
      }

      printf("---[ByteRingArray Test push_test {push_test4} case1] [OK]--- \n");
      break;
  }

  //case4
  //data:[1,2,3,4(start),5(end)]
  while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ringarray->push(1);
      ringarray->push(2);
      ringarray->push(3);
      ringarray->push(4);
      ringarray->push(5);
      ringarray->setStartIndex(3);
      ringarray->setEndIndex(4);
      ringarray->setStatus(st(ByteRingArray)::Partial);

      ByteArray data = createByteArray(4);
      data[0] = 10;
      data[1] = 11;
      data[2] = 12;
      data[3] = 13;
      //[11,12,13,4,10]
      ringarray->push(data);

      if(ringarray->at(0) != 11 || ringarray->at(1) != 12
        ||ringarray->at(2) != 13 || ringarray->at(3) != 4
        ||ringarray->at(4) != 10) {
        printf("ring[0] is %d \n",ringarray->at(0));
        printf("ring[1] is %d \n",ringarray->at(1));
        printf("ring[2] is %d \n",ringarray->at(2));
        printf("ring[3] is %d \n",ringarray->at(3));
        printf("ring[4] is %d \n",ringarray->at(4));
        printf("---[ByteRingArray Test push_test {push_test5} case1] [FAILED]--- \n");
        return 0;
      }

      printf("---[ByteRingArray Test push_test {push_test5} case1] [OK]--- \n");
      break;
  }

  //case5
  //data:[1,2,3,4,5(start/end)]
  while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ringarray->push(1);
      ringarray->push(2);
      ringarray->push(3);
      ringarray->push(4);
      ringarray->push(5);
      ringarray->setStartIndex(4);
      ringarray->setEndIndex(4);
      ringarray->setStatus(st(ByteRingArray)::Empty);

      ByteArray data = createByteArray(5);
      data[0] = 10;
      data[1] = 11;
      data[2] = 12;
      data[3] = 13;
      data[4] = 14;
      //[11,12,13,14,10]
      ringarray->push(data);

      if(ringarray->at(0) != 11 || ringarray->at(1) != 12
        ||ringarray->at(2) != 13 || ringarray->at(3) != 14
        ||ringarray->at(4) != 10) {
        printf("ring[0] is %d \n",ringarray->at(0));
        printf("ring[1] is %d \n",ringarray->at(1));
        printf("ring[2] is %d \n",ringarray->at(2));
        printf("ring[3] is %d \n",ringarray->at(3));
        printf("ring[4] is %d \n",ringarray->at(4));
        printf("---[ByteRingArray Test push_test {push_test6} case1] [FAILED]--- \n");
        return 0;
      }

      printf("---[ByteRingArray Test push_test {push_test6} case1] [OK]--- \n");
      break;
  }

  //case6
  //data:[1(end),2,3,4,5(start)]
  while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ringarray->push(1);
      ringarray->push(2);
      ringarray->push(3);
      ringarray->push(4);
      ringarray->push(5);
      ringarray->setStartIndex(4);
      ringarray->setEndIndex(0);
      ringarray->setStatus(st(ByteRingArray)::Empty);

      ByteArray data = createByteArray(4);
      data[0] = 10;
      data[1] = 11;
      data[2] = 12;
      data[3] = 13;
      //[10,11,12,13,5]
      ringarray->push(data);

      if(ringarray->at(0) != 10 || ringarray->at(1) != 11
        ||ringarray->at(2) != 12 || ringarray->at(3) != 13
        ||ringarray->at(4) != 5) {
        printf("ring[0] is %d \n",ringarray->at(0));
        printf("ring[1] is %d \n",ringarray->at(1));
        printf("ring[2] is %d \n",ringarray->at(2));
        printf("ring[3] is %d \n",ringarray->at(3));
        printf("ring[4] is %d \n",ringarray->at(4));
        printf("---[ByteRingArray Test push_test {push_test7} case1] [FAILED]--- \n");
        return 0;
      }

      printf("---[ByteRingArray Test push_test {push_test7} case1] [OK]--- \n");
      break;
  }

  //case7
  //data:[1,2(end),3,4,5(start)]
  while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ringarray->push(1);
      ringarray->push(2);
      ringarray->push(3);
      ringarray->push(4);
      ringarray->push(5);
      ringarray->setStartIndex(4);
      ringarray->setEndIndex(1);
      ringarray->setStatus(st(ByteRingArray)::Empty);

      ByteArray data = createByteArray(3);
      data[0] = 10;
      data[1] = 11;
      data[2] = 12;
      //[1,10,11,12,5]
      ringarray->push(data);

      if(ringarray->at(0) != 1 || ringarray->at(1) != 10
        ||ringarray->at(2) != 11 || ringarray->at(3) != 12
        ||ringarray->at(4) != 5) {
        printf("ring[0] is %d \n",ringarray->at(0));
        printf("ring[1] is %d \n",ringarray->at(1));
        printf("ring[2] is %d \n",ringarray->at(2));
        printf("ring[3] is %d \n",ringarray->at(3));
        printf("ring[4] is %d \n",ringarray->at(4));
        printf("---[ByteRingArray Test push_test {push_test8} case1] [FAILED]--- \n");
        return 0;
      }

      printf("---[ByteRingArray Test push_test {push_test8} case1] [OK]--- \n");
      break;
  }

  //case7
  //data:[1,2,3(end),4,5(start)]
  while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ringarray->push(1);
      ringarray->push(2);
      ringarray->push(3);
      ringarray->push(4);
      ringarray->push(5);
      ringarray->setStartIndex(4);
      ringarray->setEndIndex(2);
      ringarray->setStatus(st(ByteRingArray)::Empty);

      ByteArray data = createByteArray(2);
      data[0] = 10;
      data[1] = 11;
      //[1,2,10,11,5]
      ringarray->push(data);

      if(ringarray->at(0) != 1 || ringarray->at(1) != 2
        ||ringarray->at(2) != 10 || ringarray->at(3) != 11
        ||ringarray->at(4) != 5) {
        printf("ring[0] is %d \n",ringarray->at(0));
        printf("ring[1] is %d \n",ringarray->at(1));
        printf("ring[2] is %d \n",ringarray->at(2));
        printf("ring[3] is %d \n",ringarray->at(3));
        printf("ring[4] is %d \n",ringarray->at(4));
        printf("---[ByteRingArray Test push_test {push_test9} case1] [FAILED]--- \n");
        return 0;
      }

      printf("---[ByteRingArray Test push_test {push_test9} case1] [OK]--- \n");
      break;
  }

  //case7
  //data:[1,2,3,4(end),5(start)]
  while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ringarray->push(1);
      ringarray->push(2);
      ringarray->push(3);
      ringarray->push(4);
      ringarray->push(5);
      ringarray->setStartIndex(4);
      ringarray->setEndIndex(3);
      ringarray->setStatus(st(ByteRingArray)::Empty);

      ByteArray data = createByteArray(1);
      data[0] = 10;
      //[1,2,3,10,5]
      ringarray->push(data);

      if(ringarray->at(0) != 1 || ringarray->at(1) != 2
        ||ringarray->at(2) != 3 || ringarray->at(3) != 10
        ||ringarray->at(4) != 5) {
        printf("ring[0] is %d \n",ringarray->at(0));
        printf("ring[1] is %d \n",ringarray->at(1));
        printf("ring[2] is %d \n",ringarray->at(2));
        printf("ring[3] is %d \n",ringarray->at(3));
        printf("ring[4] is %d \n",ringarray->at(4));
        printf("---[ByteRingArray Test push_test {push_test10} case1] [FAILED]--- \n");
        return 0;
      }

      printf("---[ByteRingArray Test push_test {push_test10} case1] [OK]--- \n");
      break;
  }

  //case7
  //data:[1,2(end),3,4(start),5]
  while(1) {
      ByteRingArray ringarray = createByteRingArray(5);
      ringarray->push(1);
      ringarray->push(2);
      ringarray->push(3);
      ringarray->push(4);
      ringarray->push(5);
      ringarray->setStartIndex(3);
      ringarray->setEndIndex(1);
      ringarray->setStatus(st(ByteRingArray)::Empty);

      ByteArray data = createByteArray(2);
      data[0] = 10;
      data[1] = 11;
      //[1,10,11,4,5]
      ringarray->push(data);

      if(ringarray->at(0) != 1 || ringarray->at(1) != 10
        ||ringarray->at(2) != 11 || ringarray->at(3) != 4
        ||ringarray->at(4) != 5) {
        printf("ring[0] is %d \n",ringarray->at(0));
        printf("ring[1] is %d \n",ringarray->at(1));
        printf("ring[2] is %d \n",ringarray->at(2));
        printf("ring[3] is %d \n",ringarray->at(3));
        printf("ring[4] is %d \n",ringarray->at(4));
        printf("---[ByteRingArray Test push_test {push_test11} case1] [FAILED]--- \n");
        return 0;
      }

      printf("---[ByteRingArray Test push_test {push_test11} case1] [OK]--- \n");
      break;
  }

  return 0;
}
