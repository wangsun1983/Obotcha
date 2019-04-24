#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "PosixShareMemory.hpp"

using namespace obotcha;

int main() {
  printf("---[PosixShareMemory Test Start]--- \n");

  int pid = fork();
  if(pid == 0) {
      printf("child process start trace1 \n");
      PosixShareMemory memory = createPosixShareMemory("shareMemory",8,PosixShareMemoryWriteRead);
      memory->init();
      char *p = new char[8];
      p[0] = 0;
      p[1] = 1;
      p[2] = 2;
      p[3] = 3;
      p[4] = 4;
      p[5] = 5;
      p[6] = 6;
      p[7] = 7;
      ByteArray arr = createByteArray(p,8);
      memory->write(arr);
      printf("child process start trace2 \n");
      while(1) {}
  } else {
      sleep(1);
      PosixShareMemory memory = createPosixShareMemory("shareMemory",8,PosixShareMemoryRead);
      printf("father process start trace1 \n");
      memory->init();

      ByteArray b = createByteArray(8);
      memory->read(b);

      char *t = b->toValue();
      printf("t[0] is %d \n",t[0]);
      printf("t[1] is %d \n",t[1]);
      printf("t[2] is %d \n",t[2]);
      printf("t[3] is %d \n",t[3]);
      printf("t[4] is %d \n",t[4]);
      printf("t[5] is %d \n",t[5]);
      printf("t[6] is %d \n",t[6]);
      printf("t[7] is %d \n",t[7]);

      while(1) {}
  }

}
