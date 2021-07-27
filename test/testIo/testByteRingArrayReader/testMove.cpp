#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"
#include "ByteRingArrayReader.hpp"
using namespace obotcha;


void testMove() {

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

      int cursor = reader->move(1);
      if(cursor != 1) {
        printf("---[ByteRingArrayReader Test move case1] [FAILED]--- \n");
        break;
      }

      cursor = reader->move(1);
      if(cursor != 2) {
        printf("---[ByteRingArrayReader Test move case2] [FAILED]--- \n");
        break;
      }

      cursor = reader->move(1);
      if(cursor != 3) {
        printf("---[ByteRingArrayReader Test move case3] [FAILED]--- \n");
        break;
      }

      cursor = reader->move(1);
      if(cursor != 4) {
        printf("---[ByteRingArrayReader Test move case4] [FAILED]--- \n");
        break;
      }

      cursor = reader->move(1);
      if(cursor != 0) {
        printf("---[ByteRingArrayReader Test move case5] [FAILED]---,cursor is %d \n",cursor);
        break;
      }

      cursor = reader->move(1);
      if(cursor != 1) {
        printf("---[ByteRingArrayReader Test move case6] [FAILED]--- \n");
        break;
      }

      printf("---[ByteRingArrayReader Test move case100] [OK]--- \n");
      break;
    }
}
