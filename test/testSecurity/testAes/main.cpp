#include "Aes.hpp"

using namespace obotcha;

extern void testAes128EncryptEcb();
extern void testAes128EncryptCbc();
extern void testAesEncryptCfb();
extern void testAesEncryptOfb128();

int main() {
  testAes128EncryptEcb();
  testAes128EncryptCbc();
  testAesEncryptCfb();
  testAesEncryptOfb128();
  return 0;
}
