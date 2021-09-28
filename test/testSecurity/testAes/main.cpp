#include "Aes.hpp"

using namespace obotcha;

extern void testAes128EncryptEcb();
extern void testAes128EncryptCbc();
extern void testAesEncryptCfb();

int main() {
  testAes128EncryptEcb();
  testAes128EncryptCbc();
  testAesEncryptCfb();
  return 0;
}
