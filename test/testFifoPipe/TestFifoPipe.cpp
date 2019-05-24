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

  printf("---[FifoPipe Test Start]--- \n");
  //Pipe pp = createPipe();
  //pp->init();


  const int testDatalength = 32;
  char testData[testDatalength];
  for(int i = 0;i<testDatalength;i++) {
    testData[i] = i;
  }

  //int writeTo(ByteArray data);
  //int readFrom(ByteArray buff);
  int pid = fork();
  if(pid == 0) {
    //child process,start write
    FifoPipe fifo = createFifoPipe("mytest123",FifoWritePipe);
    fifo->init();
    sleep(1);
    ByteArray array = createByteArray(&testData[0],testDatalength);
    fifo->writeTo(array);
    return 1;
  } else {
    ByteArray array = createByteArray(testDatalength);
    FifoPipe fifo = createFifoPipe("mytest123",FifoReadPipe);
    fifo->init();
    int length = fifo->readFrom(array);
    if(length != testDatalength) {
      printf("---[FifoPipe Test {writeTo/readFrom()} case1] [FAILED]--- \n");
    }

    for(int i = 0; i < testDatalength;i++) {
      if(array->at(i) != i) {
        printf("---[FifoPipe Test {writeTo/readFrom()} case2] [FAILED]--- \n");
        break;
      }
    }
    printf("---[FifoPipe Test {writeTo/readFrom()} case3] [Success]--- \n");
  }

  //int release();
  pid = fork();
  if(pid == 0) {
    //child process,start write
    FifoPipe fifo = createFifoPipe("mytest123",FifoWritePipe);
    fifo->init();
    sleep(1);
    fifo->release();
    return 1
  } else {
    ByteArray array = createByteArray(testDatalength);
    FifoPipe fifo = createFifoPipe("mytest123",FifoReadPipe);
    fifo->init();
    sleep(1);
    int length = fifo->readFrom(array);
    if(length != 0) {
      printf("---[FifoPipe Test {release()} case1] [FAILED]--- \n");
    }

    printf("---[FifoPipe Test {release()} case2] [Success]--- \n");
  }
}
