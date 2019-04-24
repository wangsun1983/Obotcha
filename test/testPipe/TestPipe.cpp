#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "Log.hpp"
#include "Pipe.hpp"
#include "ByteArray.hpp"

using namespace obotcha;

int main() {

  printf("---[Pipe Test Start]--- \n");
  Pipe pp = createPipe();
  pp->init();

  int pid = fork();
  if(pid == 0) {
    //child process
    ByteArray array = createByteArray(8);
    array->toValue()[0] = 0;
    array->toValue()[1] = 1;
    array->toValue()[2] = 2;
    array->toValue()[3] = 3;
    array->toValue()[4] = 4;
    array->toValue()[5] = 5;
    array->toValue()[6] = 6;
    array->toValue()[7] = 7;
    printf("child start write \n");
    pp->writeTo(WritePipe,array);
  } else {
    ByteArray array = createByteArray(8);
    printf("father start read \n");
    int length = pp->readFrom(ReadPipe,array);
    printf("read length is %d \n",length);
    printf("read array[0] is %d \n",array->toValue()[0]);
    printf("read array[1] is %d \n",array->toValue()[1]);
    printf("read array[2] is %d \n",array->toValue()[2]);
    printf("read array[3] is %d \n",array->toValue()[3]);

  }

}
