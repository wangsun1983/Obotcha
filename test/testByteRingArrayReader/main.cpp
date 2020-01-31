#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"

using namespace obotcha;

extern void test_readnext();
extern void test_pop();

int main() {
  //test_readnext();
  test_pop();
}
