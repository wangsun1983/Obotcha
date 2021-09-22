#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Barrier.hpp"
#include "ByteRingArray.hpp"

using namespace obotcha;

void testPopTo() {
    //
    while(1) {

        //case1
        ByteRingArray array = createByteRingArray(5);
        array->push(1);
        array->push(2);
        array->push(3);
        array->push(4);
        array->push(5);

        ByteRingArray data1 = createByteRingArray(array);
        data1->setEndIndex(0);
        data1->setSize(5);

        ByteRingArray arr1 = createByteRingArray(data1);

        //
        ByteArray result = arr1->popTo(0);
        if(result->size() != 1) {
            printf("---[ByteRingArray Test popTo case1] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 1) {
            printf("---[ByteRingArray Test popTo case2] [FAILED]--- \n");
            break;
        }

        arr1 = createByteRingArray(data1);
        result = arr1->popTo(1);
        if(result->size() != 2) {
            printf("---[ByteRingArray Test popTo case3] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 1 || result[1] != 2) {
            printf("---[ByteRingArray Test popTo case4] [FAILED]--- \n");
            break;
        }

        arr1 = createByteRingArray(data1);
        result = arr1->popTo(2);
        if(result->size() != 3) {
            printf("---[ByteRingArray Test popTo case5] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 1 || result[1] != 2 || result[2] != 3) {
            printf("---[ByteRingArray Test popTo case6] [FAILED]--- \n");
            break;
        }

        arr1 = createByteRingArray(data1);
        result = arr1->popTo(3);
        if(result->size() != 4) {
            printf("---[ByteRingArray Test popTo case7] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 1 || result[1] != 2 || result[2] != 3 || result[3] != 4) {
            printf("---[ByteRingArray Test popTo case8] [FAILED]--- \n");
            break;
        }

        arr1 = createByteRingArray(data1);
        result = arr1->popTo(4);
        if(result->size() != 5) {
            printf("---[ByteRingArray Test popTo case9] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 1 || result[1] != 2 || result[2] != 3 || result[3] != 4 || result[4] != 5) {
            printf("---[ByteRingArray Test popTo case10] [FAILED]--- \n");
            break;
        }

        //
        data1->setEndIndex(1);
        data1->setSize(5);
        arr1 = createByteRingArray(data1);

        result = arr1->popTo(1);
        if(result->size() != 1) {
            printf("---[ByteRingArray Test popTo case11] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 2) {
            printf("---[ByteRingArray Test popTo case12] [FAILED]--- \n");
            break;
        }

        arr1 = createByteRingArray(data1);
        result = arr1->popTo(2);
        if(result->size() != 2) {
            printf("---[ByteRingArray Test popTo case13] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 2 || result[1] != 3) {
            printf("---[ByteRingArray Test popTo case14] [FAILED]--- \n");
            break;
        }

        arr1 = createByteRingArray(data1);
        result = arr1->popTo(3);
        if(result->size() != 3) {
            printf("---[ByteRingArray Test popTo case15] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 2 || result[1] != 3 || result[2] != 4) {
            printf("---[ByteRingArray Test popTo case16] [FAILED]--- \n");
            break;
        }

        arr1 = createByteRingArray(data1);
        result = arr1->popTo(4);
        if(result->size() != 4) {
            printf("---[ByteRingArray Test popTo case17] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 2 || result[1] != 3 || result[2] != 4 || result[3] != 5) {
            printf("---[ByteRingArray Test popTo case18] [FAILED]--- \n");
            break;
        }

        arr1 = createByteRingArray(data1);
        result = arr1->popTo(0);
        if(result->size() != 5) {
            printf("---[ByteRingArray Test popTo case19] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 2 || result[1] != 3 || result[2] != 4 || result[3] != 5 || result[4] != 1) {
            printf("---[ByteRingArray Test popTo case20] [FAILED]--- \n");
            break;
        }

        //
        data1->setEndIndex(2);
        data1->setSize(5);
        arr1 = createByteRingArray(data1);

        result = arr1->popTo(2);
        if(result->size() != 1) {
            printf("---[ByteRingArray Test popTo case21] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 3) {
            printf("---[ByteRingArray Test popTo case22] [FAILED]--- \n");
            break;
        }

        arr1 = createByteRingArray(data1);
        result = arr1->popTo(3);
        if(result->size() != 2) {
            printf("---[ByteRingArray Test popTo case23] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 3 || result[1] != 4) {
            printf("---[ByteRingArray Test popTo case24] [FAILED]--- \n");
            break;
        }

        arr1 = createByteRingArray(data1);
        result = arr1->popTo(4);
        if(result->size() != 3) {
            printf("---[ByteRingArray Test popTo case25] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 3 || result[1] != 4 || result[2] != 5) {
            printf("---[ByteRingArray Test popTo case26] [FAILED]--- \n");
            break;
        }

        arr1 = createByteRingArray(data1);
        result = arr1->popTo(0);
        if(result->size() != 4) {
            printf("---[ByteRingArray Test popTo case27] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 3 || result[1] != 4 || result[2] != 5 || result[3] != 1) {
            printf("---[ByteRingArray Test popTo case28] [FAILED]--- \n");
            break;
        }

        arr1 = createByteRingArray(data1);
        result = arr1->popTo(1);
        if(result->size() != 5) {
            printf("---[ByteRingArray Test popTo case29] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 3 || result[1] != 4 || result[2] != 5 || result[3] != 1 || result[4] != 2) {
            printf("---[ByteRingArray Test popTo case30] [FAILED]--- \n");
            break;
        }

        //
        data1->setEndIndex(3);
        data1->setSize(5);
        arr1 = createByteRingArray(data1);

        result = arr1->popTo(3);
        if(result->size() != 1) {
            printf("---[ByteRingArray Test popTo case31] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 4) {
            printf("---[ByteRingArray Test popTo case32] [FAILED]--- \n");
            break;
        }

        arr1 = createByteRingArray(data1);
        result = arr1->popTo(4);
        if(result->size() != 2) {
            printf("---[ByteRingArray Test popTo case33] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 4 || result[1] != 5) {
            printf("---[ByteRingArray Test popTo case34] [FAILED]--- \n");
            break;
        }

        arr1 = createByteRingArray(data1);
        result = arr1->popTo(0);
        if(result->size() != 3) {
            printf("---[ByteRingArray Test popTo case35] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 4 || result[1] != 5 || result[2] != 1) {
            printf("---[ByteRingArray Test popTo case36] [FAILED]--- \n");
            break;
        }

        arr1 = createByteRingArray(data1);
        result = arr1->popTo(1);
        if(result->size() != 4) {
            printf("---[ByteRingArray Test popTo case37] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 4 || result[1] != 5 || result[2] != 1 || result[3] != 2) {
            printf("---[ByteRingArray Test popTo case38] [FAILED]--- \n");
            break;
        }

        arr1 = createByteRingArray(data1);
        result = arr1->popTo(2);
        if(result->size() != 5) {
            printf("---[ByteRingArray Test popTo case39] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 4 || result[1] != 5 || result[2] != 1 || result[3] != 2 || result[4] != 3) {
            printf("---[ByteRingArray Test popTo case40] [FAILED]--- \n");
            break;
        }

        //
        data1->setEndIndex(4);
        data1->setSize(5);
        arr1 = createByteRingArray(data1);

        result = arr1->popTo(4);
        if(result->size() != 1) {
            printf("---[ByteRingArray Test popTo case51] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 5) {
            printf("---[ByteRingArray Test popTo case52] [FAILED]--- \n");
            break;
        }

        arr1 = createByteRingArray(data1);
        result = arr1->popTo(0);
        if(result->size() != 2) {
            printf("---[ByteRingArray Test popTo case53] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 5 || result[1] != 1) {
            printf("---[ByteRingArray Test popTo case54] [FAILED]--- \n");
            break;
        }

        arr1 = createByteRingArray(data1);
        result = arr1->popTo(1);
        if(result->size() != 3) {
            printf("---[ByteRingArray Test popTo case55] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 5 || result[1] != 1 || result[2] != 2) {
            printf("---[ByteRingArray Test popTo case56] [FAILED]--- \n");
            break;
        }

        arr1 = createByteRingArray(data1);
        result = arr1->popTo(2);
        if(result->size() != 4) {
            printf("---[ByteRingArray Test popTo case57] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 5 || result[1] != 1 || result[2] != 2 || result[3] != 3) {
            printf("---[ByteRingArray Test popTo case58] [FAILED]--- \n");
            break;
        }

        arr1 = createByteRingArray(data1);
        result = arr1->popTo(3);
        if(result->size() != 5) {
            printf("---[ByteRingArray Test popTo case59] [FAILED]--- ,size is %d\n",result->size());
            break;
        }

        if(result[0] != 5 || result[1] != 1 || result[2] != 2 || result[3] != 3 || result[4] != 4) {
            printf("---[ByteRingArray Test popTo case60] [FAILED]--- \n");
            break;
        }


        printf("---[ByteRingArray Test popTo case100] [OK]--- \n");
        break;
    }
    return;
}
