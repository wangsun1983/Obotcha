#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "LocalSocketClient.hpp"
#include "PosixSem.hpp"
#include "System.hpp"


using namespace obotcha;

int main() {
  printf("---[PosixSem Test Start]--- \n");

  //wait()
  int pid = fork();
  if(pid == 0) {
      PosixSem sem = createPosixSem("sem_test1",0);
      sem->init();
      int ret = sem->wait();
      return 1;
  } else {
      PosixSem sem = createPosixSem("sem_test1",0);
      sem->init();
      sleep(1);
      sem->post();
      wait(nullptr);//wait for child process
      printf("---[PosixSem Test {wait()} case1] [Success]--- \n");
  }

  //wait(long)
  pid = fork();
  if(pid == 0) {
      PosixSem sem = createPosixSem("sem_test2",0);
      sem->init();
      sleep(1);
      int ret = sem->post();
      return 1;
  } else {
      PosixSem sem = createPosixSem("sem_test2",0);
      sem->init();
      long current = st(System)::currentTimeMillis();
      sem->wait();
      long waittime = (st(System)::currentTimeMillis() - current);
      if(waittime > 1005 || waittime <1000) {
          printf("---[PosixSem Test {wait(long)} case1] [FAILED]--- \n");
          return 1;
      }

      printf("---[PosixSem Test {wait()} case1] [Success]--- \n");
  }

  //int getValue();
  {
      PosixSem sem3 = createPosixSem("sem_test3",100);
      sem3->clean();
      sem3->init();
      sem3->post();
      if(sem3->getValue() != 101) {
        printf("sem3 value is %d \n",sem3->getValue());
        printf("---[PosixSem Test {getValue()} case1] [FAILED]--- \n");
      }
      printf("---[PosixSem Test {getValue()} case2] [Success]--- \n");
  }

}
