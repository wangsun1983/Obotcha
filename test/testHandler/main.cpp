#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"

using namespace obotcha;

extern int testHandler();
extern int testSendMessageDelayed();
extern int testHasMessage();
extern int testHandlerSize();
extern int testHandlerMultiSend();
extern int testHandlerRemove();

int main() {
  testHandlerRemove();
  testHandlerMultiSend();
  testHandlerSize();
  testHandler();
  testSendMessageDelayed();
  testHasMessage();
}
