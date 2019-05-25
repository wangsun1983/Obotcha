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
#include "System.hpp"

using namespace obotcha;

int main() {

  printf("---[PosixMq Test Start]--- \n");
  PosixMq mq = createPosixMq("abc",SendMq);
  mq->clean();

  const int testDatalength = 32;
  char testData[testDatalength];
  for(int i = 0;i<testDatalength;i++) {
    testData[i] = i;
  }

  //int send(ByteArray data);
  //int receive(ByteArray buff);
  int pid = fork();
  if(pid == 0) {
    //child process
    PosixMq mq = createPosixMq("abc",SendMq);
    mq->init();
    ByteArray array = createByteArray(&testData[0],testDatalength);
    //printf("child start write \n");
    mq->send(array);
    mq->release();
    return 1;
  } else {
    ByteArray array = createByteArray(testDatalength);
    //sleep(1);
    //printf("father start read \n");
    PosixMq mq = createPosixMq("abc",RecvMq);
    mq->init();
    int length = mq->receive(array);
    if(length < testDatalength) {
        printf("---[PosixMq Test {send/receive()} case1] [FAILED]--- \n");
        return 1;
    }

    for(int i = 0; i < testDatalength;i++) {
      if(array->at(i) != i) {
        printf("---[PosixMq Test {send/receive()} case2] [FAILED]--- \n");
        break;
      }
    }

    printf("---[PosixMq Test {send/receive()} case3] [Success]--- \n");
  }

  //send(ByteArray data,int prio);
  //int receive(ByteArray buff);
  pid = fork();
  if(pid == 0) {
    //child process
    PosixMq mq = createPosixMq("abc",SendMq);
    mq->init();
    ByteArray array = createByteArray(&testData[0],testDatalength);
    //printf("child start write \n");
    mq->send(array);

    ByteArray array2 = createByteArray(&testData[1],testDatalength-1);
    mq->send(array2,PosixMqPriortyNormal);
    mq->release();
    return 1;
  } else {
    sleep(1);
    ByteArray array = createByteArray(testDatalength);
    //sleep(1);
    //printf("father start read \n");
    PosixMq mq = createPosixMq("abc",RecvMq);
    mq->init();
    int length = mq->receive(array);

    if(length != (testDatalength-1)) {
        printf("---[PosixMq Test {send/receive()} case4] [FAILED]--- \n");
        return 1;
    }

    for(int i = 0; i < testDatalength - 1;i++) {
      if(array->at(i) != (i+1)) {
        printf("---[PosixMq Test {send/receive()} case5] [FAILED]--- \n");
        break;
      }
    }

    length = mq->receive(array);

    if(length != testDatalength) {
        printf("---[PosixMq Test {send/receive()} case6] [FAILED]--- \n");
        return 1;
    }

    for(int i = 0; i < testDatalength;i++) {
      if(array->at(i) != i) {
        printf("---[PosixMq Test {send/receive()} case6] [FAILED]--- \n");
        break;
      }
    }

    printf("---[PosixMq Test {send/receive()} case7] [Success]--- \n");
  }

  //send(ByteArray data,int prio);

  //int receiveTimeout(ByteArray buff);
  pid = fork();
  if(pid == 0) {
    //child process
    return 1;
  } else {
    ByteArray array = createByteArray(testDatalength);
    //sleep(1);
    //printf("father start read \n");
    PosixMq mq = createPosixMq("abc",RecvMq);
    mq->init();
    long current = st(System)::currentTimeMillis();
    int length = mq->receiveTimeout(array,500);

    if(st(System)::currentTimeMillis() - current != 500) {
      printf("---[PosixMq Test {receiveTimeout()} case1] [FAILED]--- \n");
      return 1;
    }

    if(length > 0) {
      printf("---[PosixMq Test {receiveTimeout()} case2] [FAILED]--- \n");
      return 1;
    }

    printf("---[PosixMq Test {receiveTimeout()} case3] [Success]--- \n");
  }

}
