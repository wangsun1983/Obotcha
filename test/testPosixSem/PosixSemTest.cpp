#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "LocalSocketClient.hpp"
#include "PosixSem.hpp"


using namespace obotcha;

int main() {
  printf("---[PosixSem Test Start]--- \n");

  int pid = fork();
  if(pid == 0) {
      PosixSem sem = createPosixSem("sem_test",1);
      sem->init();
      printf("child process start wait,sem value is %d \n",sem->getValue());
      sem->wait();
      printf("child process start trace1 \n");
      sleep(5);
      printf("child process start trace2 \n");
      sem->post();
      printf("child process start trace3 \n");
      while(1) {}
  } else {
      printf("father process start wait \n");
      sleep(1);
      printf("father process start trace1 \n");
      PosixSem sem = createPosixSem("sem_test",1);
      sem->init();
      printf("father process start trace2 sem value is %d \n",sem->getValue());
      sem->wait();
      printf("father process start trace3 \n");
      sem->post();
      printf("father process start trace4 \n");
      while(1) {}
  }

}
