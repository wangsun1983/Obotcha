#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "Log.hpp"

int main() {

  Long l = createLong(1);
  printf("value is %ld \n",l->toValue());

  LOGD("val is ",l);
}
