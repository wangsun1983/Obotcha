#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"

using namespace obotcha;

extern void testReadNext();
extern void test_pop();
//extern void testpopall();
extern void testReadableLength();

int main() {
  //test_readnext();
  //testpopall();
  testReadNext();
  testReadableLength();
  test_pop();
}
