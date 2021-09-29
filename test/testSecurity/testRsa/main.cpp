#include "Rsa.hpp"

using namespace obotcha;

extern void testRsa3Pcks1();
extern void testRsaf4Pcks1();

int main() {
  testRsa3Pcks1();
  testRsaf4Pcks1();
  return 0;
}
