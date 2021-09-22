#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"

using namespace obotcha;


void testPopAll() {

  //case1
  //data:[1(start),2,3,4,5(end)]
  while(1) {
    ByteRingArray array = createByteRingArray(5);
    array->push(1);
    array->push(2);
    array->push(3);
    array->push(4);
    array->push(5);

    ByteRingArray arr1 = createByteRingArray(array);
    arr1->setEndIndex(0);
    arr1->setSize(5);

    ByteArray result = arr1->popAll();
    if(result->size() != 5) {
      printf("---[ByteRingArray Test PopAll case1] [FAILED]--- \n");
      break;
    }

    if(result[0] != 1 || result[1] != 2 || result[2] != 3 || result[3] != 4 || result[4] != 5) {
      printf("---[ByteRingArray Test PopAll case2] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(0);
    arr1->setSize(4);

    result = arr1->popAll();
    if(result->size() != 4) {
      printf("---[ByteRingArray Test PopAll case2] [FAILED]--- \n");
      break;
    }

    if(result[0] != 2 || result[1] != 3 || result[2] != 4 || result[3] != 5) {
      printf("---[ByteRingArray Test PopAll case3] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(0);
    arr1->setSize(3);

    result = arr1->popAll();
    if(result->size() != 3) {
      printf("---[ByteRingArray Test PopAll case4] [FAILED]--- \n");
      break;
    }

    if(result[0] != 3 || result[1] != 4 || result[2] != 5) {
      printf("---[ByteRingArray Test PopAll case5] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(0);
    arr1->setSize(2);

    result = arr1->popAll();
    if(result->size() != 2) {
      printf("---[ByteRingArray Test PopAll case6] [FAILED]--- \n");
      break;
    }

    if(result[0] != 4 || result[1] != 5) {
      printf("---[ByteRingArray Test PopAll case7] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(0);
    arr1->setSize(1);

    result = arr1->popAll();
    if(result->size() != 1) {
      printf("---[ByteRingArray Test PopAll case8] [FAILED]--- \n");
      break;
    }

    if(result[0] != 5) {
      printf("---[ByteRingArray Test PopAll case9] [FAILED]--- \n");
      break;
    }

    //
    arr1 = createByteRingArray(array);
    arr1->setEndIndex(1);
    arr1->setSize(5);

    result = arr1->popAll();
    if(result->size() != 5) {
      printf("---[ByteRingArray Test PopAll case10] [FAILED]--- \n");
      break;
    }

    if(result[0] != 2 || result[1] != 3 || result[2] != 4 || result[3] != 5 || result[4] != 1) {
      printf("---[ByteRingArray Test PopAll case11] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(1);
    arr1->setSize(4);

    result = arr1->popAll();
    if(result->size() != 4) {
      printf("---[ByteRingArray Test PopAll case12] [FAILED]--- \n");
      break;
    }

    if(result[0] != 3 || result[1] != 4 || result[2] != 5 || result[3] != 1) {
      printf("---[ByteRingArray Test PopAll case13] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(1);
    arr1->setSize(3);

    result = arr1->popAll();
    if(result->size() != 3) {
      printf("---[ByteRingArray Test PopAll case14] [FAILED]--- \n");
      break;
    }

    if(result[0] != 4 || result[1] != 5 || result[2] != 1) {
      printf("---[ByteRingArray Test PopAll case15] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(1);
    arr1->setSize(2);

    result = arr1->popAll();
    if(result->size() != 2) {
      printf("---[ByteRingArray Test PopAll case16] [FAILED]--- \n");
      break;
    }

    if(result[0] != 5 || result[1] != 1) {
      printf("---[ByteRingArray Test PopAll case17] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(1);
    arr1->setSize(1);

    result = arr1->popAll();
    if(result->size() != 1) {
      printf("---[ByteRingArray Test PopAll case18] [FAILED]--- \n");
      break;
    }

    if(result[0] != 1) {
      printf("---[ByteRingArray Test PopAll case19] [FAILED]--- \n");
      break;
    }

    //
    arr1 = createByteRingArray(array);
    arr1->setEndIndex(2);
    arr1->setSize(5);

    result = arr1->popAll();
    if(result->size() != 5) {
      printf("---[ByteRingArray Test PopAll case20] [FAILED]--- \n");
      break;
    }

    if(result[0] != 3 || result[1] != 4 || result[2] != 5 || result[3] != 1 || result[4] != 2) {
      printf("---[ByteRingArray Test PopAll case21] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(2);
    arr1->setSize(4);

    result = arr1->popAll();
    if(result->size() != 4) {
      printf("---[ByteRingArray Test PopAll case20] [FAILED]--- \n");
      break;
    }

    if(result[0] != 4 || result[1] != 5 || result[2] != 1 || result[3] != 2) {
      printf("---[ByteRingArray Test PopAll case21] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(2);
    arr1->setSize(3);

    result = arr1->popAll();
    if(result->size() != 3) {
      printf("---[ByteRingArray Test PopAll case21] [FAILED]--- \n");
      break;
    }

    if(result[0] != 5 || result[1] != 1 || result[2] != 2) {
      printf("---[ByteRingArray Test PopAll case22] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(2);
    arr1->setSize(2);

    result = arr1->popAll();
    if(result->size() != 2) {
      printf("---[ByteRingArray Test PopAll case23] [FAILED]--- \n");
      break;
    }

    if(result[0] != 1 || result[1] != 2) {
      printf("---[ByteRingArray Test PopAll case24] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(2);
    arr1->setSize(1);

    result = arr1->popAll();
    if(result->size() != 1) {
      printf("---[ByteRingArray Test PopAll case25] [FAILED]--- \n");
      break;
    }

    if(result[0] != 2) {
      printf("---[ByteRingArray Test PopAll case26] [FAILED]--- \n");
      break;
    }

    //
    arr1 = createByteRingArray(array);
    arr1->setEndIndex(2);
    arr1->setSize(5);

    result = arr1->popAll();
    if(result->size() != 5) {
      printf("---[ByteRingArray Test PopAll case27] [FAILED]--- \n");
      break;
    }

    if(result[0] != 3 || result[1] != 4 || result[2] != 5 || result[3] != 1 || result[4] != 2) {
      printf("---[ByteRingArray Test PopAll case28] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(2);
    arr1->setSize(4);

    result = arr1->popAll();
    if(result->size() != 4) {
      printf("---[ByteRingArray Test PopAll case29] [FAILED]--- \n");
      break;
    }

    if(result[0] != 4 || result[1] != 5 || result[2] != 1 || result[3] != 2) {
      printf("---[ByteRingArray Test PopAll case30] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(2);
    arr1->setSize(3);

    result = arr1->popAll();
    if(result->size() != 3) {
      printf("---[ByteRingArray Test PopAll case31] [FAILED]--- \n");
      break;
    }

    if(result[0] != 5 || result[1] != 1 || result[2] != 2) {
      printf("---[ByteRingArray Test PopAll case32] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(2);
    arr1->setSize(2);

    result = arr1->popAll();
    if(result->size() != 2) {
      printf("---[ByteRingArray Test PopAll case32] [FAILED]--- \n");
      break;
    }

    if(result[0] != 1 || result[1] != 2) {
      printf("---[ByteRingArray Test PopAll case33] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(2);
    arr1->setSize(1);

    result = arr1->popAll();
    if(result->size() != 1) {
      printf("---[ByteRingArray Test PopAll case34] [FAILED]--- \n");
      break;
    }

    if(result[0] != 2) {
      printf("---[ByteRingArray Test PopAll case35] [FAILED]--- \n");
      break;
    }

    //
    arr1 = createByteRingArray(array);
    arr1->setEndIndex(3);
    arr1->setSize(5);

    result = arr1->popAll();
    if(result->size() != 5) {
      printf("---[ByteRingArray Test PopAll case36] [FAILED]--- \n");
      break;
    }

    if(result[0] != 4 || result[1] != 5 || result[2] != 1 || result[3] != 2 || result[4] != 3) {
      printf("---[ByteRingArray Test PopAll case37] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(3);
    arr1->setSize(4);

    result = arr1->popAll();
    if(result->size() != 4) {
      printf("---[ByteRingArray Test PopAll case38] [FAILED]--- \n");
      break;
    }

    if(result[0] != 5|| result[1] != 1 || result[2] != 2 || result[3] != 3) {
      printf("---[ByteRingArray Test PopAll case39] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(3);
    arr1->setSize(3);

    result = arr1->popAll();
    if(result->size() != 3) {
      printf("---[ByteRingArray Test PopAll case38] [FAILED]--- \n");
      break;
    }

    if(result[0] != 1|| result[1] != 2 || result[2] != 3) {
      printf("---[ByteRingArray Test PopAll case39] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(3);
    arr1->setSize(2);

    result = arr1->popAll();
    if(result->size() != 2) {
      printf("---[ByteRingArray Test PopAll case40] [FAILED]--- \n");
      break;
    }

    if(result[0] != 2|| result[1] != 3) {
      printf("---[ByteRingArray Test PopAll case41] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(3);
    arr1->setSize(1);

    result = arr1->popAll();
    if(result->size() != 1) {
      printf("---[ByteRingArray Test PopAll case42] [FAILED]--- \n");
      break;
    }

    if(result[0] != 3) {
      printf("---[ByteRingArray Test PopAll case43] [FAILED]--- \n");
      break;
    }

    //
    arr1 = createByteRingArray(array);
    arr1->setEndIndex(4);
    arr1->setSize(5);

    result = arr1->popAll();
    if(result->size() != 5) {
      printf("---[ByteRingArray Test PopAll case44] [FAILED]--- \n");
      break;
    }

    if(result[0] != 5 || result[1] != 1 || result[2] != 2 || result[3] != 3 || result[4] != 4) {
      printf("---[ByteRingArray Test PopAll case45] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(4);
    arr1->setSize(4);

    result = arr1->popAll();
    if(result->size() != 4) {
      printf("---[ByteRingArray Test PopAll case46] [FAILED]--- \n");
      break;
    }

    if(result[0] != 1 || result[1] != 2 || result[2] != 3 || result[3] != 4) {
      printf("---[ByteRingArray Test PopAll case47] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(4);
    arr1->setSize(3);

    result = arr1->popAll();
    if(result->size() != 3) {
      printf("---[ByteRingArray Test PopAll case48] [FAILED]--- \n");
      break;
    }

    if(result[0] != 2 || result[1] != 3 || result[2] != 4) {
      printf("---[ByteRingArray Test PopAll case49] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(4);
    arr1->setSize(2);

    result = arr1->popAll();
    if(result->size() != 2) {
      printf("---[ByteRingArray Test PopAll case50] [FAILED]--- \n");
      break;
    }

    if(result[0] != 3 || result[1] != 4) {
      printf("---[ByteRingArray Test PopAll case51] [FAILED]--- \n");
      break;
    }

    arr1 = createByteRingArray(array);
    arr1->setEndIndex(4);
    arr1->setSize(1);

    result = arr1->popAll();
    if(result->size() != 1) {
      printf("---[ByteRingArray Test PopAll case52] [FAILED]--- \n");
      break;
    }

    if(result[0] != 4) {
      printf("---[ByteRingArray Test PopAll case53] [FAILED]--- \n");
      break;
    }

    printf("---[ByteRingArray Test PopAll case99] [OK]--- \n");
    break;
  }

  return;
}
