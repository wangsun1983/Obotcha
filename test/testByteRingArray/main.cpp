#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"
#include "ByteRingArray.hpp"

using namespace obotcha;

extern void normal_test();
extern void push_test();

int main() {
  normal_test();
  push_test();
}
