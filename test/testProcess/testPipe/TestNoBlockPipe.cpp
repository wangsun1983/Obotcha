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

int testNoBlockPipe() {

  const int testDatalength = 32;
  char testData[testDatalength];
  for(int i = 0;i<testDatalength;i++) {
    testData[i] = i;
  }

  //int writeTo(PipeType type,ByteArray data);
  //int readFrom(PipeType type,ByteArray buff);
  Pipe pp = createPipe(PipeNonBlock);
  pp->init();

  int pid = fork();
  if(pid == 0) {
     //child process
     ByteArray array = createByteArray(&testData[0],testDatalength);
     pp->writeTo(array);
     exit(0);
  } else {
     sleep(1);
     ByteArray array = createByteArray(testDatalength);
     int length = pp->readFrom(array);

     if(length < testDatalength) {
         printf("---[Pipe Test {noblock writeTo/readFrom()} case1] [FAILED]--- \n");
         return 1;
     }

     for(int i = 0; i < testDatalength;i++) {
       if(array->at(i) != i) {
         printf("---[Pipe Test {noblock writeTo/readFrom()} case2] [FAILED]--- \n");
         break;
       }
     }
   }

   printf("---[Pipe Test {noblock writeTo/readFrom()} case3] [Success]--- \n");


   Pipe pp1_1 = createPipe(PipeNonBlock);
   pp1_1->init();

   pid = fork();
   if(pid == 0) {
      //child process
      sleep(1);
      ByteArray array = createByteArray(&testData[0],testDatalength);
      pp->writeTo(array);
      exit(0);
   } else {
      ByteArray array = createByteArray(testDatalength);
      int length = pp->readFrom(array);
      if(length != -1) {
          printf("---[Pipe Test {noblock writeTo/readFrom()} case4] [FAILED]--- \n");
          return 1;
      }
    }

    printf("---[Pipe Test {noblock writeTo/readFrom()} case5] [Success]--- \n");


   //int closePipe(PipeType type);
   Pipe pp2 = createPipe(PipeNonBlock);
   pp2->init();

   pid = fork();
   if(pid == 0) {
      //child process
      pp2->closeReadPipe();
      ByteArray array = createByteArray(&testData[0],testDatalength);
      pp2->writeTo(array);
      exit(0);
   } else {
      sleep(1);
      pp2->closeWritePipe();
      ByteArray array = createByteArray(testDatalength);
      int length = pp2->readFrom(array);

      if(length < testDatalength) {
          printf("---[Pipe Test {noblock closePipe()} case1] [FAILED]--- \n");
          return 1;
      }

      for(int i = 0; i < testDatalength;i++) {
        if(array->at(i) != i) {
          printf("---[Pipe Test {noblock closePipe()} case2] [FAILED]--- \n");
          break;
        }
      }
    }

    printf("---[Pipe Test {noblock closePipe()} case3] [Success]--- \n");

    //int closePipe(PipeType type);
    Pipe pp3 = createPipe(PipeNonBlock);
    pp3->init();

    pid = fork();
    if(pid == 0) {
       //child process
       pp3->closeWritePipe();
       ByteArray array = createByteArray(testDatalength);
       int length = pp3->readFrom(array);
       if(length > 0) {
           printf("---[Pipe Test {noblock closePipe()} case4] [FAILED]--- \n");
       }
       exit(0);
    } else {
       pp3->closeWritePipe();
       ByteArray array = createByteArray(&testData[0],testDatalength);
       int result = pp3->writeTo(array);
       if(result >= 0) {
           printf("---[Pipe Test {noblock closePipe()} case5] [FAILED]--- \n");
       }
     }

     printf("---[Pipe Test {noblock closePipe()} case6] [Success]--- \n");

}
