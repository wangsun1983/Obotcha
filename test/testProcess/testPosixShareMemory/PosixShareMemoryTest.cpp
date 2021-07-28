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
  const int testDatalength = 32;
  char testData[testDatalength];
  for(int i = 0;i<testDatalength;i++) {
    testData[i] = i;
  }

  //int write(ByteArray);
  //int read(ByteArray);
  //int read(int index,ByteArray);
  //int read(int);
  int pid = fork();
  if(pid == 0) {
      PosixShareMemory memory = createPosixShareMemory("/shareMemoryabc",testDatalength,PosixShareMemoryWriteRead);
      memory->init();
      ByteArray arr = createByteArray(&testData[0],32);
      memory->write(arr);
      return 0;
  } else {
      sleep(1);
      PosixShareMemory memory = createPosixShareMemory("/shareMemoryabc",testDatalength,PosixShareMemoryRead);
      memory->init();

      ByteArray b = createByteArray(32);
      int length = memory->read(b);

      if(length < testDatalength) {
          printf("---[PosixShareMemory Test {write/read()} case1] [FAILED]--- \n");
          return 1;
      }

      for(int i = 0; i < testDatalength;i++) {
        if(b->at(i) != i) {
          printf("---[PosixShareMemory Test {write/read()} case2] [FAILED]--- \n");
          break;
        }

        if(memory->read(i) != i) {
          printf("---[PosixShareMemory Test {write/read()} case3] [FAILED]--- \n");
          break;
        }
      }

      ByteArray b2 = createByteArray(64);
      int length2 = memory->read(b2);
      if(length2 < testDatalength) {
          printf("---[PosixShareMemory Test {write/read()} case4] [FAILED]--- \n");
          return 1;
      }

      for(int i = 0; i < testDatalength;i++) {
        if(b2->at(i) != i) {
          printf("---[PosixShareMemory Test {write/read()} case5] [FAILED]--- \n");
          break;
        }
      }

      ByteArray b3 = createByteArray(64);
      if(memory->read(256,b3) != -PosixShmReadOverSize) {
        printf("---[PosixShareMemory Test {write/read()} case6] [FAILED]--- \n");
      }

      if(memory->read(16,b3) < 0) {
        printf("---[PosixShareMemory Test {write/read()} case7] [FAILED]--- \n");
      }

      for(int i = 0; i < (testDatalength-16);i++) {
        if(b3->at(i) != i) {
          printf("---[PosixShareMemory Test {write/read()} case8] [FAILED]--- \n");
          break;
        }
      }

      printf("---[PosixShareMemory Test {write/read()} case9] [Success]--- \n");

      //while(1) {}
  }

  //int write(ByteArray);
  //int write(int index,ByteArray);
  //int write(int index,char v);
  pid = fork();
  if(pid == 0) {
    PosixShareMemory memory = createPosixShareMemory("/shareMemoryabc",testDatalength,PosixShareMemoryWriteRead);
    memory->init();
    ByteArray arr = createByteArray(&testData[0],32);
    if(memory->write(256,arr) != -PosixShmWriteOverSize) {
      printf("---[PosixShareMemory Test {write/read()} case10] [FAILED]--- \n");
    }

    if(memory->write(256,'c') != -PosixShmWriteOverSize) {
      printf("---[PosixShareMemory Test {write/read()} case11] [FAILED]--- \n");
    }

    memory->write(16,'c');
    return 1;
  } else {
    sleep(1);
    PosixShareMemory memory = createPosixShareMemory("/shareMemoryabc",testDatalength,PosixShareMemoryWriteRead);
    memory->init();
    if(memory->read(16) != 'c') {
      printf("---[PosixShareMemory Test {write/read()} case12] [FAILED]--- \n");
    }

    printf("---[PosixShareMemory Test {write/read()} case13] [Success]--- \n");
  }

}
