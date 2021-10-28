#include "HttpPacketParser.hpp"

using namespace obotcha;

extern void testHttpParse();
extern void testMultiMessageParse();
extern void testChunkOneByteParse();
extern void testMultiPartOneByteParse();

int main() {
  //testMultiMessageParse();
  //testChunkOneByteParse();
  testMultiPartOneByteParse();
  //testHttpParse();
  return 0;
}
