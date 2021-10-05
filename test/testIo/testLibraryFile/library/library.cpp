#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

using namespace obotcha;

DECLARE_CLASS(MyTestData) {
public:
  int data1;
  int data2;
};

#ifdef __cplusplus
extern "C"{
#endif

int start(int v1,int v2) {
  return v1+v2;
}

#ifdef __cplusplus
}
#endif
