#include "Des.hpp"

using namespace obotcha;

extern void testDesEncryptEcb();
extern void testDesEncryptCbc();
extern void testAesEncryptEcb();

int main() {
  testDesEncryptEcb();
  testDesEncryptCbc();
  return 0;
}
