#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "Log.hpp"
#include "Pipe.hpp"
#include "PosixMq.hpp"

using namespace obotcha;

int main() {

  printf("---[Pipe Test Start]--- \n");

  int pid = fork();
  if(pid == 0) {
    //child process
    PosixMq mq = createPosixMq("abc",SendMq);
    mq->init();

    ByteArray array = createByteArray(8);
    array->toValue()[0] = 0;
    array->toValue()[1] = 1;
    array->toValue()[2] = 2;
    array->toValue()[3] = 3;
    array->toValue()[4] = 4;
    array->toValue()[5] = 5;
    array->toValue()[6] = 6;
    array->toValue()[7] = 0;
    printf("child start write \n");
    mq->send(array);
  } else {
    ByteArray array = createByteArray(1024);
    sleep(1);
    printf("father start read \n");
    PosixMq mq = createPosixMq("abc",RecvMq);
    mq->init();
    int length = mq->receive(array);
    printf("read length is %d \n",length);
    printf("read array[0] is %d \n",array->toValue()[0]);
    printf("read array[1] is %d \n",array->toValue()[1]);
    printf("read array[2] is %d \n",array->toValue()[2]);
    printf("read array[3] is %d \n",array->toValue()[3]);
  }

}
