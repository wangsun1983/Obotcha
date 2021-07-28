#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "LocalSocketClient.hpp"
#include "SocketListener.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyTestData) {
public:
  int data1;
  int data2;
};

#ifdef __cplusplus
extern "C"{
#endif    

void start(int v1,int v2) {
  MyTestData t = createMyTestData();
  t->data1 = 3;
  t->data2 = 4;

  t->data1 += 100;
  t->data2 += 120;
  printf("data1 is %d,data2 is %d \n",t->data1,t->data2);
}

#ifdef __cplusplus
}
#endif
