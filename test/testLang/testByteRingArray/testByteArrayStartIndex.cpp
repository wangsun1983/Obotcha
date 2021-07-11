#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"

using namespace obotcha;


int testStartIndex() {

  //case1
  //data:[1(start),2,3,4,5(end)]
    ByteRingArray array = createByteRingArray(5);
    array->push(1);
    if(array->getStartIndex() != 0) {
      printf("---[ByteRingArray Test Start Index case1] [FAILED]--- \n");
      return 0;
    }

    array->push(2); 
    if(array->getStartIndex() != 0) {
      printf("---[ByteRingArray Test Start Index case2] [FAILED]--- \n");
      return 0;
    }

    array->push(3);
     if(array->getStartIndex() != 0) {
      printf("---[ByteRingArray Test Start Index case3] [FAILED]--- \n");
      return 0;
    }

    array->push(4);
    if(array->getStartIndex() != 0) {
      printf("---[ByteRingArray Test Start Index case4] [FAILED]--- \n");
      return 0;
    }
    
    array->push(5);
    if(array->getStartIndex() != 0) {
      printf("---[ByteRingArray Test Start Index case5] [FAILED]--- \n");
      return 0;
    }

    //mIndex 0
    array->setNextIndex(0);
    array->setSize(1);
    if(array->getStartIndex() != 4) {
      printf("---[ByteRingArray Test Start Index case6] [FAILED]--- \n");
      return 0;
    }

    array->setNextIndex(0);
    array->setSize(2);
    if(array->getStartIndex() != 3) {
      printf("---[ByteRingArray Test Start Index case7] [FAILED]--- \n");
      return 0;
    }

    array->setNextIndex(0);
    array->setSize(3);
    if(array->getStartIndex() != 2) {
      printf("---[ByteRingArray Test Start Index case8] [FAILED]--- \n");
      return 0;
    }

    array->setNextIndex(0);
    array->setSize(4);
    if(array->getStartIndex() != 1) {
      printf("---[ByteRingArray Test Start Index case9] [FAILED]--- \n");
      return 0;
    }

    array->setNextIndex(0);
    array->setSize(5);
    if(array->getStartIndex() != 0) {
      printf("---[ByteRingArray Test Start Index case10] [FAILED]--- \n");
      return 0;
    }

    //mIndex 1
    array->setNextIndex(1);
    array->setSize(1);
    if(array->getStartIndex() != 0) {
      printf("---[ByteRingArray Test Start Index case11] [FAILED]--- \n");
      return 0;
    }

    array->setNextIndex(1);
    array->setSize(2);
    if(array->getStartIndex() != 4) {
      printf("---[ByteRingArray Test Start Index case12] [FAILED]--- \n");
      return 0;
    }

    array->setNextIndex(1);
    array->setSize(3);
    if(array->getStartIndex() != 3) {
      printf("---[ByteRingArray Test Start Index case13] [FAILED]--- \n");
      return 0;
    }

    array->setNextIndex(1);
    array->setSize(4);
    if(array->getStartIndex() != 2) {
      printf("---[ByteRingArray Test Start Index case14] [FAILED]--- \n");
      return 0;
    }

    array->setNextIndex(1);
    array->setSize(5);
    if(array->getStartIndex() != 1) {
      printf("---[ByteRingArray Test Start Index case15] [FAILED]--- \n");
      return 0;
    }

    //mIndex 2
    array->setNextIndex(2);
    array->setSize(1);
    if(array->getStartIndex() != 1) {
      printf("---[ByteRingArray Test Start Index case16] [FAILED]--- \n");
      return 0;
    }

    array->setNextIndex(2);
    array->setSize(2);
    if(array->getStartIndex() != 0) {
      printf("---[ByteRingArray Test Start Index case17] [FAILED]--- \n");
      return 0;
    }

    array->setNextIndex(2);
    array->setSize(3);
    if(array->getStartIndex() != 4) {
      printf("---[ByteRingArray Test Start Index case18] [FAILED]--- \n");
      return 0;
    }

    array->setNextIndex(2);
    array->setSize(4);
    if(array->getStartIndex() != 3) {
      printf("---[ByteRingArray Test Start Index case19] [FAILED]--- \n");
      return 0;
    }

    array->setNextIndex(2);
    array->setSize(5);
    if(array->getStartIndex() != 2) {
      printf("---[ByteRingArray Test Start Index case20] [FAILED]--- \n");
      return 0;
    }

    //mIndex 3
    array->setNextIndex(3);
    array->setSize(1);
    if(array->getStartIndex() != 2) {
      printf("---[ByteRingArray Test Start Index case21] [FAILED]--- \n");
      return 0;
    }

    array->setNextIndex(3);
    array->setSize(2);
    if(array->getStartIndex() != 1) {
      printf("---[ByteRingArray Test Start Index case22] [FAILED]--- \n");
      return 0;
    }

    array->setNextIndex(3);
    array->setSize(3);
    if(array->getStartIndex() != 0) {
      printf("---[ByteRingArray Test Start Index case23] [FAILED]--- \n");
      return 0;
    }

    array->setNextIndex(3);
    array->setSize(4);
    if(array->getStartIndex() != 4) {
      printf("---[ByteRingArray Test Start Index case24] [FAILED]--- \n");
      return 0;
    }

    array->setNextIndex(3);
    array->setSize(5);
    if(array->getStartIndex() != 3) {
      printf("---[ByteRingArray Test Start Index case25] [FAILED]--- \n");
      return 0;
    }

    //mIndex 4
    array->setNextIndex(4);
    array->setSize(1);
    if(array->getStartIndex() != 3) {
      printf("---[ByteRingArray Test Start Index case26] [FAILED]--- \n");
      return 0;
    }

    array->setNextIndex(4);
    array->setSize(2);
    if(array->getStartIndex() != 2) {
      printf("---[ByteRingArray Test Start Index case27] [FAILED]--- \n");
      return 0;
    }

    array->setNextIndex(4);
    array->setSize(3);
    if(array->getStartIndex() != 1) {
      printf("---[ByteRingArray Test Start Index case28] [FAILED]--- \n");
      return 0;
    }

    array->setNextIndex(4);
    array->setSize(4);
    if(array->getStartIndex() != 0) {
      printf("---[ByteRingArray Test Start Index case29] [FAILED]--- \n");
      return 0;
    }

    array->setNextIndex(4);
    array->setSize(5);
    if(array->getStartIndex() != 4) {
      printf("---[ByteRingArray Test Start Index case30] [FAILED]--- \n");
      return 0;
    }

}
