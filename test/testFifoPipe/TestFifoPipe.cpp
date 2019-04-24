#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "Log.hpp"
#include "FifoPipe.hpp"
#include "ByteArray.hpp"

using namespace obotcha;

int main() {

  printf("---[Pipe Test Start]--- \n");
  //Pipe pp = createPipe();
  //pp->init();

  int pid = fork();
  if(pid == 0) {
    //child process,start write
    printf("child start write1 \n");
    FifoPipe fifo = createFifoPipe("mytest123",FifoWritePipe);
    fifo->init();
    sleep(1);
    printf("child start write2 \n");
    ByteArray array = createByteArray(8);
    array->toValue()[0] = 0;
    array->toValue()[1] = 1;
    array->toValue()[2] = 2;
    array->toValue()[3] = 3;
    array->toValue()[4] = 4;
    array->toValue()[5] = 5;
    array->toValue()[6] = 6;
    array->toValue()[7] = 0;
    printf("child start write3 \n");
    fifo->writeTo(array);
    printf("child start write4 \n");
  } else {
    ByteArray array = createByteArray(8);
    printf("father start read \n");
    FifoPipe fifo = createFifoPipe("mytest123",FifoReadPipe);
    fifo->init();
    printf("father start read1 \n");

    int length = fifo->readFrom(array);
    printf("read length is %d \n",length);
    printf("read array[0] is %d \n",array->toValue()[0]);
    printf("read array[1] is %d \n",array->toValue()[1]);
    printf("read array[2] is %d \n",array->toValue()[2]);
    printf("read array[3] is %d \n",array->toValue()[3]);

  }

}
