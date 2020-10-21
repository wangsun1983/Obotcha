#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"

using namespace obotcha;

extern int testHandler();
extern int testSendMessageDelayed();
extern int testHasMessage();

int main() {
  //testHandler();
  //testSendMessageDelayed();
  testHasMessage();
}
