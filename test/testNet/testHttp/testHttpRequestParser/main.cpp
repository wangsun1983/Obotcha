#include "HttpPacketParser.hpp"

using namespace obotcha;

extern void testHttpParse();
extern void testMultiMessageParse();

int main() {
  testMultiMessageParse();
  //testHttpParse();
  return 0;
}
