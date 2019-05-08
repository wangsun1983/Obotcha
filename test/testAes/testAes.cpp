#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Aes.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

using namespace obotcha;

int main() {
    Aes aes = createAes(AesTypeECB);
    //aes->genKey("abc_key1","mykeyhaha",AES_ENCRYPT);
    aes->loadKey("abc_key1",AES_ENCRYPT);

    String r1 = aes->encode(createString("hello world"));
    printf("r1 is %s \n",r1->toChars());

    Aes aes2 = createAes(AesTypeECB);
    //aes2->genKey("abc_key2","mykeyhaha",AES_DECRYPT);
    aes2->loadKey("abc_key2",AES_DECRYPT);

    String r2 = aes2->decode(r1);
    printf("r2 is %s \n",r2->toChars());
}
