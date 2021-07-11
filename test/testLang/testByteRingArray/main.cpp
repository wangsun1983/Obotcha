#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"

using namespace obotcha;

extern void normal_test();
extern void push_test();
extern int testByteRingArrayPush2();
extern int testByteRingArrayPop();
extern int testStartIndex();
extern int testPopAll();

int main() {
  //testStartIndex();
  //normal_test();
  //push_test();
  //testByteRingArrayPush2();
  //testByteRingArrayPop();
    testPopAll();
}
