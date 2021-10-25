#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"

using namespace obotcha;


void testByteRingArrayPopWithParam() {

  //
  while(1) {
    ByteRingArray array = createByteRingArray(5);
    array->push(1);
    array->push(2);
    array->push(3);
    array->push(4);
    array->push(5);

    //------------
    ByteRingArray arr1 = createByteRingArray(array);
    arr1->setEndIndex(0);
    arr1->setSize(5);

    ByteArray result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case1] [FAILED]--- \n");
      break;
    }

    if(result[0] != 1) {
      printf("---[ByteRingArray Test pop with param case2] [FAILED]--- \n");
      break;
    }

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case3] [FAILED]--- \n");
      break;
    }

    if(result[0] != 2) {
      printf("---[ByteRingArray Test pop with param case4] [FAILED]--- \n");
      break;
    }

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case5] [FAILED]--- \n");
      break;
    }

    if(result[0] != 3) {
      printf("---[ByteRingArray Test pop with param case6] [FAILED]--- \n");
      break;
    }

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case7] [FAILED]--- \n");
      break;
    }

    if(result[0] != 4) {
      printf("---[ByteRingArray Test pop with param case8] [FAILED]--- \n");
      break;
    }

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case9] [FAILED]--- \n");
      break;
    }

    if(result[0] != 5) {
      printf("---[ByteRingArray Test pop with param case10] [FAILED]--- \n");
      break;
    }

    bool isException = false;
    try {
      result = arr1->pop(1);
    } catch(...){
      isException = true;
    }

    if(!isException) {
      printf("---[ByteRingArray Test pop with param case11] [FAILED]--- \n");
      break;
    }

    //------------
    arr1 = createByteRingArray(array);
    arr1->setEndIndex(4);
    arr1->setSize(5);

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case12] [FAILED]--- \n");
      break;
    }

    if(result[0] != 5) {
      printf("---[ByteRingArray Test pop with param case13] [FAILED]--- \n");
      break;
    }

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case14] [FAILED]--- \n");
      break;
    }

    if(result[0] != 1) {
      printf("---[ByteRingArray Test pop with param case15] [FAILED]--- \n");
      break;
    }

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case16] [FAILED]--- \n");
      break;
    }

    if(result[0] != 2) {
      printf("---[ByteRingArray Test pop with param case17] [FAILED]--- \n");
      break;
    }

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case18] [FAILED]--- \n");
      break;
    }

    if(result[0] != 3) {
      printf("---[ByteRingArray Test pop with param case19] [FAILED]--- \n");
      break;
    }

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case20] [FAILED]--- \n");
      break;
    }

    if(result[0] != 4) {
      printf("---[ByteRingArray Test pop with param case21] [FAILED]--- \n");
      break;
    }

    //------------
    arr1 = createByteRingArray(array);
    arr1->setEndIndex(3);
    arr1->setSize(5);

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case22] [FAILED]--- \n");
      break;
    }

    if(result[0] != 4) {
      printf("---[ByteRingArray Test pop with param case23] [FAILED]--- \n");
      break;
    }

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case24] [FAILED]--- \n");
      break;
    }

    if(result[0] != 5) {
      printf("---[ByteRingArray Test pop with param case25] [FAILED]--- \n");
      break;
    }

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case26] [FAILED]--- \n");
      break;
    }

    if(result[0] != 1) {
      printf("---[ByteRingArray Test pop with param case27] [FAILED]--- \n");
      break;
    }

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case28] [FAILED]--- \n");
      break;
    }

    if(result[0] != 2) {
      printf("---[ByteRingArray Test pop with param case29] [FAILED]--- \n");
      break;
    }

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case30] [FAILED]--- \n");
      break;
    }

    if(result[0] != 3) {
      printf("---[ByteRingArray Test pop with param case31] [FAILED]--- \n");
      break;
    }

    isException = false;
    try {
      result = arr1->pop(1);
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      printf("---[ByteRingArray Test pop with param case32] [FAILED]--- \n");
      break;
    }

    //------------
    arr1 = createByteRingArray(array);
    arr1->setEndIndex(2);
    arr1->setSize(5);

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case42] [FAILED]--- \n");
      break;
    }

    if(result[0] != 3) {
      printf("---[ByteRingArray Test pop with param case43] [FAILED]--- \n");
      break;
    }

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case44] [FAILED]--- \n");
      break;
    }

    if(result[0] != 4) {
      printf("---[ByteRingArray Test pop with param case45] [FAILED]--- \n");
      break;
    }

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case46] [FAILED]--- \n");
      break;
    }

    if(result[0] != 5) {
      printf("---[ByteRingArray Test pop with param case47] [FAILED]--- \n");
      break;
    }

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case48] [FAILED]--- \n");
      break;
    }

    if(result[0] != 1) {
      printf("---[ByteRingArray Test pop with param case49] [FAILED]--- \n");
      break;
    }

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case50] [FAILED]--- \n");
      break;
    }

    if(result[0] != 2) {
      printf("---[ByteRingArray Test pop with param case51] [FAILED]--- \n");
      break;
    }

    isException = false;
    try {
      result = arr1->pop(1);
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      printf("---[ByteRingArray Test pop with param case52] [FAILED]--- \n");
      break;
    }

    //------------
    arr1 = createByteRingArray(array);
    arr1->setEndIndex(1);
    arr1->setSize(5);

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case42] [FAILED]--- \n");
      break;
    }

    if(result[0] != 2) {
      printf("---[ByteRingArray Test pop with param case43] [FAILED]--- \n");
      break;
    }

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case44] [FAILED]--- \n");
      break;
    }

    if(result[0] != 3) {
      printf("---[ByteRingArray Test pop with param case45] [FAILED]--- \n");
      break;
    }

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case46] [FAILED]--- \n");
      break;
    }

    if(result[0] != 4) {
      printf("---[ByteRingArray Test pop with param case47] [FAILED]--- \n");
      break;
    }

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case48] [FAILED]--- \n");
      break;
    }

    if(result[0] != 5) {
      printf("---[ByteRingArray Test pop with param case49] [FAILED]--- \n");
      break;
    }

    result = arr1->pop(1);
    if(result->size() != 1) {
      printf("---[ByteRingArray Test pop with param case50] [FAILED]--- \n");
      break;
    }

    if(result[0] != 1) {
      printf("---[ByteRingArray Test pop with param case51] [FAILED]--- \n");
      break;
    }

    isException = false;
    try {
      result = arr1->pop(1);
    } catch(...) {
      isException = true;
    }

    if(!isException) {
      printf("---[ByteRingArray Test pop with param case52] [FAILED]--- \n");
      break;
    }

    printf("---[ByteRingArray Test pop with param case100] [OK]--- \n");
    break;
  }
  return;
}
