#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"
#include "ByteRingArrayReader.hpp"
using namespace obotcha;


void test_readnext() {
    //{1,2,3,4,5,6}
    ByteRingArray ringarray = createByteRingArray(6);
    ByteArray array = createByteArray(6);
    array->fill(0,1);
    array->fill(1,2);
    array->fill(2,3); 
    array->fill(3,4);
    array->fill(4,5);
    array->fill(5,6);

    ringarray->push(array);

    ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
    int status = ByteRingArrayReadContinue;

    byte ind = 1;
    while(status != ByteRingArrayReadComplete) {
        byte value = 0;
        status = reader->readNext(value);
        if(value != ind) {
            printf("---[ByteRingArrayReader Test {readnext(byte val)} case0] [FAILED]--- \n");
            break;
        }

        ind++;  
    }

    //{x,2,3,4,5,x}
    ringarray = createByteRingArray(6);
    array = createByteArray(5);
    array->fill(0,1);
    array->fill(1,2);
    array->fill(2,3); 
    array->fill(3,4);
    array->fill(4,5);

    ringarray->push(array);
    ringarray->pop(1);

    reader = createByteRingArrayReader(ringarray);
    status = ByteRingArrayReadContinue;

    ind = 2;
    while(status != ByteRingArrayReadComplete) {
        byte value = 0;
        status = reader->readNext(value);
        if(value != ind) {
            printf("---[ByteRingArrayReader Test {readnext(byte val)} case1] [FAILED]--- \n");
            break;
        }
        ind++;
    }

    //{1,2,3,4,5,x}
    ringarray = createByteRingArray(6);
    array = createByteArray(5);
    array->fill(0,1);
    array->fill(1,2);
    array->fill(2,3); 
    array->fill(3,4);
    array->fill(4,5);
    ringarray->push(array);
    reader = createByteRingArrayReader(ringarray);
    status = ByteRingArrayReadContinue;

    ind = 1;
    while(status != ByteRingArrayReadComplete) {
        byte value = 0;
        status = reader->readNext(value);
        if(value != ind) {
            printf("---[ByteRingArrayReader Test {readnext(byte val)} case2] [FAILED]--- \n");
            break;
        }
        ind++;
    }

    if(ind != 6) {
        printf("---[ByteRingArrayReader Test {readnext(byte val)} case3] [FAILED]--- \n");
        return;
    }

    //{x,2,3,4,5,6}
    ringarray = createByteRingArray(6);
    array = createByteArray(6);
    array->fill(0,1);
    array->fill(1,2);
    array->fill(2,3); 
    array->fill(3,4);
    array->fill(4,5);
    array->fill(5,6);

    ringarray->push(array);
    ringarray->pop(1);

    reader = createByteRingArrayReader(ringarray);
    status = ByteRingArrayReadContinue;
    ind = 2;
    while(status != ByteRingArrayReadComplete) {
        byte value = 0;
        status = reader->readNext(value);
        if(value != ind) {
            printf("---[ByteRingArrayReader Test {readnext(byte val)} case4,value is %d,ind is %d] [FAILED]--- \n",value,ind);
            break;
        }
        ind++;
    }

    if(ind != 7) {
        printf("---[ByteRingArrayReader Test {readnext(byte val)} case5] [FAILED]--- \n");
        return;
    }


    printf("---[ByteRingArrayReader Test {readnext(byte val)} case10] [OK]--- \n");
    
}
