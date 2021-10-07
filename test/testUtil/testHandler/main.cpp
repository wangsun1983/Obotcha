#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"

using namespace obotcha;

extern void testHandler();
extern void testSendMessageDelayed();
extern void testHasMessage();
extern void testHandlerSize();
extern void testHandlerMultiSend();
extern void testHandlerRemove();
extern void testHandlerLambda();

int main() {
  testHandlerLambda();
  testHandlerRemove();
  testHandlerMultiSend();
  testHandlerSize();
  testHandler();
  testSendMessageDelayed();
  testHasMessage();
  return 0;
}
