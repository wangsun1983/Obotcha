#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Aes.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

using namespace obotcha;

extern int test_aes_key_gen();
extern int test_aes_key_load();
extern int test_aes_ecb();
extern int test_aes_cbc();

int main() {
#if 0    
    Aes aes = createAes(AesTypeECB);
    aes->genKey(createString("dec_abc_key1"),createString("enc_abc_key1"));
    aes->loadKey("enc_abc_key1",AES_ENCRYPT);

    String r1 = aes->encrypt(createString("hello world"));
    printf("r1 is %s \n",r1->toChars());

    Aes aes2 = createAes(AesTypeECB);
    //aes2->genKey("abc_key2","mykeyhaha",AES_DECRYPT);
    aes2->loadKey("dec_abc_key1",AES_DECRYPT);

    String r2 = aes2->decrypt(r1);
    printf("r2 is %s \n",r2->toChars());
#endif
    test_aes_key_gen();

    test_aes_key_load();

    test_aes_ecb();

    test_aes_cbc();
}
