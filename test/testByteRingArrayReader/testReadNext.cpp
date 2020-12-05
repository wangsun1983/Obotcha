#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"
#include "ByteRingArrayReader.hpp"
using namespace obotcha;


void testReadNext() {
  //case1
  //data:[1(start/end),2,3,4,5]
  while(1) {
    ByteRingArray ringarray = createByteRingArray(5);
    ringarray->push(1);
    ringarray->push(2);
    ringarray->push(3);
    ringarray->push(4);
    ringarray->push(5);
    byte v1;
    byte v2;
    byte v3;
    byte v4;
    byte v5;
    int startIndex = ringarray->getStartIndex();
    int endIndex = ringarray->getEndIndex();
    ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
    if(reader->readNext(v1) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext} case1] [FAIL]--- \n");
        return;
    }
    if(v1 != 1) {
        printf("---[ByteRingArrayReader Test {testReadNext} case1_1] [FAIL]--- \n");
        return;
    }
    if(reader->readNext(v2) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext} case2] [FAIL]--- \n");
        return;
    }
    if(v2 != 2) {
        printf("---[ByteRingArrayReader Test {testReadNext} case2_1] [FAIL]--- \n");
        return;
    }
    if(reader->readNext(v3) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext} case3] [FAIL]--- \n");
        return;
    }
    if(v3 != 3) {
        printf("---[ByteRingArrayReader Test {testReadNext} case3_1] [FAIL]--- \n");
        return;
    }
    if(reader->readNext(v4) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext} case4] [FAIL]--- \n");
        return;
    }
    if(v4 != 4) {
        printf("---[ByteRingArrayReader Test {testReadNext} case4_1] [FAIL]--- \n");
        return;
    }

    if(reader->readNext(v5) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext} case5] [FAIL]--- \n");
        return;
    }
    if(v5 != 5) {
        printf("---[ByteRingArrayReader Test {testReadNext} case5_1] [FAIL]--- \n");
        return;
    }
    byte end;
    if(reader->readNext(end) != ByteRingArrayReadComplete) {
        printf("---[ByteRingArrayReader Test {testReadNext} case6] [FAIL]--- \n");
        return;
    }
    ByteArray popdata = reader->pop();
    if(popdata->size() != 5) {
        printf("---[ByteRingArrayReader Test {testReadNext} case7] [FAIL]--- \n");
        return;
    }
    if(popdata[0]!= 1 ||popdata[1] != 2||popdata[2] != 3||popdata[3] != 4||popdata[4] != 5) {
        printf("---[ByteRingArrayReader Test {testReadNext} case8] [FAIL]--- \n");
        return;
    }

    printf("---[ByteRingArrayReader Test {testReadNext} case9] [OK]--- \n");
    break;
  }

  //case2
  //data:[1(end),2(start),3,4,5]
  while(1) {
    ByteRingArray ringarray = createByteRingArray(5);
    ringarray->push(1);
    ringarray->push(2);
    ringarray->push(3);
    ringarray->push(4);
    ringarray->push(5);
    byte v1;
    byte v2;
    byte v3;
    byte v4;
    byte v5;
    ringarray->setStartIndex(1);
    ringarray->setEndIndex(0);

    ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
    if(reader->readNext(v1) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition2} case1] [FAIL]--- \n");
        return;
    }
    if(v1 != 2) {
        printf("---[ByteRingArrayReader Test {testReadNext condition2} case1_1] [FAIL]--- \n");
        return;
    }

    if(reader->readNext(v2) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition2} case2] [FAIL]--- \n");
        return;
    }
    if(v2 != 3) {
        printf("---[ByteRingArrayReader Test {testReadNext condition2} case2_1] [FAIL]--- \n");
        return;
    }

    if(reader->readNext(v3) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition2} case3] [FAIL]--- \n");
        return;
    }
    if(v3 != 4) {
        printf("---[ByteRingArrayReader Test {testReadNext condition2} case3_1] [FAIL]--- \n");
        return;
    }

    if(reader->readNext(v4) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition2} case4] [FAIL]--- \n");
        return;
    }
    if(v4 != 5) {
        printf("---[ByteRingArrayReader Test {testReadNext condition2} case4_1] [FAIL]--- \n");
        return;
    }

    byte end;
    int result = reader->readNext(end);
    if(result != ByteRingArrayReadComplete) {
        printf("---[ByteRingArrayReader Test {testReadNext condition2} case6] [FAIL]--- \n");
        return;
    }

    ByteArray popdata = reader->pop();
    if(popdata->size() != 4) {
        printf("---[ByteRingArrayReader Test {testReadNext condition2} case7] [FAIL]--- \n");
        return;
    }

    if(popdata[0]!= 2 ||popdata[1] != 3||popdata[2] != 4||popdata[3] != 5) {
        printf("---[ByteRingArrayReader Test {testReadNext condition2} case8] [FAIL]--- \n");
        return;
    }

    printf("---[ByteRingArrayReader Test {testReadNext condition2} case7] [OK]--- \n");
    break;
  }

  //case3
  //data:[1(end),2,3(start),4,5]
  while(1) {
    ByteRingArray ringarray = createByteRingArray(5);
    ringarray->push(1);
    ringarray->push(2);
    ringarray->push(3);
    ringarray->push(4);
    ringarray->push(5);
    byte v1;
    byte v2;
    byte v3;
    byte v4;
    byte v5;
    ringarray->setStartIndex(2);
    ringarray->setEndIndex(0);

    ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
    if(reader->readNext(v1) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition3} case1] [FAIL]--- \n");
        return;
    }
    if(v1 != 3) {
        printf("---[ByteRingArrayReader Test {testReadNext condition3} case1_1] [FAIL]--- \n");
        return;
    }

    if(reader->readNext(v2) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition3} case2] [FAIL]--- \n");
        return;
    }
    if(v2 != 4) {
        printf("---[ByteRingArrayReader Test {testReadNext condition3} case2_1] [FAIL]--- \n");
        return;
    }

    if(reader->readNext(v3) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition3} case3] [FAIL]--- \n");
        return;
    }
    if(v3 != 5) {
        printf("---[ByteRingArrayReader Test {testReadNext condition3} case3_1] [FAIL]--- \n");
        return;
    }

    byte end;
    if(reader->readNext(end) != ByteRingArrayReadComplete) {
        printf("---[ByteRingArrayReader Test {testReadNext condition3} case6] [FAIL]--- \n");
        return;
    }

    ByteArray popdata = reader->pop();
    if(popdata->size() != 3) {
        printf("---[ByteRingArrayReader Test {testReadNext condition3} case7] [FAIL]--- \n");
        return;
    }

    if(popdata[0]!= 3 ||popdata[1] != 4||popdata[2] != 5) {
        printf("---[ByteRingArrayReader Test {testReadNext condition3} case8] [FAIL]--- \n");
        return;
    }

    printf("---[ByteRingArrayReader Test {testReadNext condition3} case7] [OK]--- \n");
    break;
  }

  //case4
  //data:[1(end),2,3,4(start),5]
  while(1) {
    ByteRingArray ringarray = createByteRingArray(5);
    ringarray->push(1);
    ringarray->push(2);
    ringarray->push(3);
    ringarray->push(4);
    ringarray->push(5);
    byte v1;
    byte v2;
    byte v3;
    byte v4;
    byte v5;
    ringarray->setStartIndex(3);
    ringarray->setEndIndex(0);

    ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
    if(reader->readNext(v1) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition4} case1] [FAIL]--- \n");
        return;
    }
    if(v1 != 4) {
        printf("---[ByteRingArrayReader Test {testReadNext condition4} case1_1] [FAIL]--- \n");
        return;
    }

    if(reader->readNext(v2) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition4} case2] [FAIL]--- \n");
        return;
    }
    if(v2 != 5) {
        printf("---[ByteRingArrayReader Test {testReadNext condition4} case2_1] [FAIL]--- \n");
        return;
    }

    byte end;
    if(reader->readNext(end) != ByteRingArrayReadComplete) {
        printf("---[ByteRingArrayReader Test {testReadNext condition4} case6] [FAIL]--- \n");
        return;
    }

    ByteArray popdata = reader->pop();
    if(popdata->size() != 2) {
        printf("---[ByteRingArrayReader Test {testReadNext condition4} case7] [FAIL]--- \n");
        return;
    }

    if(popdata[0]!= 4 ||popdata[1] != 5) {
        printf("---[ByteRingArrayReader Test {testReadNext condition4} case8] [FAIL]--- \n");
        return;
    }

    printf("---[ByteRingArrayReader Test {testReadNext condition4} case7] [OK]--- \n");
    break;
  }

  //case5
  //data:[1(end),2,3,4,5(start)]
  while(1) {
    ByteRingArray ringarray = createByteRingArray(5);
    ringarray->push(1);
    ringarray->push(2);
    ringarray->push(3);
    ringarray->push(4);
    ringarray->push(5);
    byte v1;
    byte v2;
    byte v3;
    byte v4;
    byte v5;
    ringarray->setStartIndex(4);
    ringarray->setEndIndex(0);

    ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
    if(reader->readNext(v1) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition5} case1] [FAIL]--- \n");
        return;
    }
    if(v1 != 5) {
        printf("---[ByteRingArrayReader Test {testReadNext condition5} case1_1] [FAIL]--- \n");
        return;
    }

    byte end;
    if(reader->readNext(end) != ByteRingArrayReadComplete) {
        printf("---[ByteRingArrayReader Test {testReadNext condition5} case6] [FAIL]--- \n");
        return;
    }

    ByteArray popdata = reader->pop();
    if(popdata->size() != 1) {
        printf("---[ByteRingArrayReader Test {testReadNext condition5} case7] [FAIL]--- \n");
        return;
    }

    if(popdata[0]!= 5) {
        printf("---[ByteRingArrayReader Test {testReadNext condition5} case8] [FAIL]--- \n");
        return;
    }

    printf("---[ByteRingArrayReader Test {testReadNext condition5} case7] [OK]--- \n");
    break;
  }

  //case5
  //data:[1,2(end/start),3,4,5]
  while(1) {
    ByteRingArray ringarray = createByteRingArray(5);
    ringarray->push(1);
    ringarray->push(2);
    ringarray->push(3);
    ringarray->push(4);
    ringarray->push(5);
    byte v1;
    byte v2;
    byte v3;
    byte v4;
    byte v5;
    ringarray->setStartIndex(1);
    ringarray->setEndIndex(1);

    ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
    if(reader->readNext(v1) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition6} case1] [FAIL]--- \n");
        return;
    }
    if(v1 != 2) {
        printf("---[ByteRingArrayReader Test {testReadNext condition6} case1_1] [FAIL]--- \n");
        return;
    }

    if(reader->readNext(v2) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition6} case2] [FAIL]--- \n");
        return;
    }
    if(v2 != 3) {
        printf("---[ByteRingArrayReader Test {testReadNext condition6} case2_1] [FAIL]--- \n");
        return;
    }

    if(reader->readNext(v3) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition6} case3] [FAIL]--- \n");
        return;
    }
    if(v3 != 4) {
        printf("---[ByteRingArrayReader Test {testReadNext condition6} case3_1] [FAIL]--- \n");
        return;
    }

    if(reader->readNext(v4) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition6} case4] [FAIL]--- \n");
        return;
    }
    if(v4 != 5) {
        printf("---[ByteRingArrayReader Test {testReadNext condition6} case4_1] [FAIL]--- \n");
        return;
    }

    if(reader->readNext(v5) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition6} case5] [FAIL]--- \n");
        return;
    }
    if(v5 != 1) {
        printf("---[ByteRingArrayReader Test {testReadNext condition6} case5_1] [FAIL]--- \n");
        return;
    }

    byte end;
    if(reader->readNext(end) != ByteRingArrayReadComplete) {
        printf("---[ByteRingArrayReader Test {testReadNext condition6} case6] [FAIL]--- \n");
        return;
    }

    ByteArray popdata = reader->pop();
    if(popdata->size() != 5) {
        printf("---[ByteRingArrayReader Test {testReadNext condition6} case7] [FAIL]--- \n");
        return;
    }

    if(popdata[0]!= 2 ||popdata[1]!= 3||popdata[2]!= 4||popdata[3]!= 5||popdata[4]!= 1) {
        printf("---[ByteRingArrayReader Test {testReadNext condition6} case8] [FAIL]--- \n");
        return;
    }

    printf("---[ByteRingArrayReader Test {testReadNext condition6} case8] [OK]--- \n");
    break;
  }

  //case6
  //data:[1,2(end),3(start),4,5]
  while(1) {
    ByteRingArray ringarray = createByteRingArray(5);
    ringarray->push(1);
    ringarray->push(2);
    ringarray->push(3);
    ringarray->push(4);
    ringarray->push(5);
    byte v1;
    byte v2;
    byte v3;
    byte v4;
    byte v5;
    ringarray->setStartIndex(2);
    ringarray->setEndIndex(1);

    ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
    if(reader->readNext(v1) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition7} case1] [FAIL]--- \n");
        return;
    }
    if(v1 != 3) {
        printf("---[ByteRingArrayReader Test {testReadNext condition7} case1_1] [FAIL]--- \n");
        return;
    }

    if(reader->readNext(v2) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition7} case2] [FAIL]--- \n");
        return;
    }
    if(v2 != 4) {
        printf("---[ByteRingArrayReader Test {testReadNext condition7} case2_1] [FAIL]--- \n");
        return;
    }

    if(reader->readNext(v3) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition7} case3] [FAIL]--- \n");
        return;
    }
    if(v3 != 5) {
        printf("---[ByteRingArrayReader Test {testReadNext condition7} case3_1] [FAIL]--- \n");
        return;
    }

    if(reader->readNext(v4) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition7} case4] [FAIL]--- \n");
        return;
    }
    if(v4 != 1) {
        printf("---[ByteRingArrayReader Test {testReadNext condition7} case4_1] [FAIL]--- \n");
        return;
    }

    byte end;
    if(reader->readNext(end) != ByteRingArrayReadComplete) {
        printf("---[ByteRingArrayReader Test {testReadNext condition7} case6] [FAIL]--- \n");
        return;
    }

    ByteArray popdata = reader->pop();
    if(popdata->size() != 4) {
        printf("---[ByteRingArrayReader Test {testReadNext condition7} case7] [FAIL]--- \n");
        return;
    }

    if(popdata[0]!= 3 ||popdata[1]!= 4||popdata[2]!= 5||popdata[3]!= 1) {
        printf("---[ByteRingArrayReader Test {testReadNext condition7} case8] [FAIL]--- \n");
        return;
    }

    printf("---[ByteRingArrayReader Test {testReadNext condition7} case8] [OK]--- \n");
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
    byte v1;
    byte v2;
    byte v3;
    byte v4;
    byte v5;
    ringarray->setStartIndex(3);
    ringarray->setEndIndex(1);

    ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
    if(reader->readNext(v1) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition8} case1] [FAIL]--- \n");
        return;
    }
    if(v1 != 4) {
        printf("---[ByteRingArrayReader Test {testReadNext condition8} case1_1] [FAIL]--- \n");
        return;
    }

    if(reader->readNext(v2) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition8} case2] [FAIL]--- \n");
        return;
    }
    if(v2 != 5) {
        printf("---[ByteRingArrayReader Test {testReadNext condition8} case2_1] [FAIL]--- \n");
        return;
    }

    if(reader->readNext(v3) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition8} case3] [FAIL]--- \n");
        return;
    }
    if(v3 != 1) {
        printf("---[ByteRingArrayReader Test {testReadNext condition8} case3_1] [FAIL]--- \n");
        return;
    }

    byte end;
    if(reader->readNext(end) != ByteRingArrayReadComplete) {
        printf("---[ByteRingArrayReader Test {testReadNext condition8} case6] [FAIL]--- \n");
        return;
    }

    ByteArray popdata = reader->pop();
    if(popdata->size() != 3) {
        printf("---[ByteRingArrayReader Test {testReadNext condition8} case7] [FAIL]--- \n");
        return;
    }

    if(popdata[0]!= 4 ||popdata[1]!= 5||popdata[2]!= 1) {
        printf("---[ByteRingArrayReader Test {testReadNext condition8} case8] [FAIL]--- \n");
        return;
    }

    printf("---[ByteRingArrayReader Test {testReadNext condition8} case8] [OK]--- \n");
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
    byte v1;
    byte v2;
    byte v3;
    byte v4;
    byte v5;
    ringarray->setStartIndex(4);
    ringarray->setEndIndex(1);

    ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
    if(reader->readNext(v1) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition9} case1] [FAIL]--- \n");
        return;
    }
    if(v1 != 5) {
        printf("---[ByteRingArrayReader Test {testReadNext condition9} case1_1] [FAIL]--- \n");
        return;
    }

    if(reader->readNext(v2) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition9} case2] [FAIL]--- \n");
        return;
    }
    if(v2 != 1) {
        printf("---[ByteRingArrayReader Test {testReadNext condition9} case2_1] [FAIL]--- \n");
        return;
    }

    byte end;
    if(reader->readNext(end) != ByteRingArrayReadComplete) {
        printf("---[ByteRingArrayReader Test {testReadNext condition9} case6] [FAIL]--- \n");
        return;
    }

    ByteArray popdata = reader->pop();
    if(popdata->size() != 2) {
        printf("---[ByteRingArrayReader Test {testReadNext condition9} case7] [FAIL]--- \n");
        return;
    }

    if(popdata[0]!= 5 ||popdata[1]!= 1) {
        printf("---[ByteRingArrayReader Test {testReadNext condition9} case8] [FAIL]--- \n");
        return;
    }

    printf("---[ByteRingArrayReader Test {testReadNext condition9} case8] [OK]--- \n");
    break;
  }

  //case8
  //data:[1(start),2(end),3,4,5]
  while(1) {
    ByteRingArray ringarray = createByteRingArray(5);
    ringarray->push(1);
    ringarray->push(2);
    ringarray->push(3);
    ringarray->push(4);
    ringarray->push(5);
    byte v1;
    byte v2;
    byte v3;
    byte v4;
    byte v5;
    ringarray->setStartIndex(0);
    ringarray->setEndIndex(1);

    ByteRingArrayReader reader = createByteRingArrayReader(ringarray);
    if(reader->readNext(v1) != ByteRingArrayReadContinue) {
        printf("---[ByteRingArrayReader Test {testReadNext condition10} case1] [FAIL]--- \n");
        return;
    }
    if(v1 != 1) {
        printf("---[ByteRingArrayReader Test {testReadNext condition10} case1_1] [FAIL]--- \n");
        return;
    }

    byte end;
    if(reader->readNext(end) != ByteRingArrayReadComplete) {
        printf("---[ByteRingArrayReader Test {testReadNext condition10} case6] [FAIL]--- \n");
        return;
    }

    ByteArray popdata = reader->pop();
    if(popdata->size() != 1) {
        printf("---[ByteRingArrayReader Test {testReadNext condition10} case7] [FAIL]--- \n");
        return;
    }

    if(popdata[0]!= 1) {
        printf("---[ByteRingArrayReader Test {testReadNext condition10} case8] [FAIL]--- \n");
        return;
    }

    printf("---[ByteRingArrayReader Test {testReadNext condition10} case8] [OK]--- \n");
    break;
  }

}
