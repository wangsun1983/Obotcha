#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Rsa.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

using namespace obotcha;

int main() {
    Rsa keyRsa = createRsa();
    keyRsa->genKey("pub_k","priv_k");

    Rsa rsa = createRsa();
    //rsa->genKey("pub_k","priv_k");
    rsa->loadPublicKey("pub_k");
    ByteArray r1 = rsa->encrypt("hello world");
    printf("r1 is %s size is %d\n",r1->toValue(),r1->size());

    Rsa rsa2 = createRsa();
    rsa2->loadPrivateKey("priv_k");
    ByteArray r2 = rsa2->decrypt(r1);
    printf("r2 is %s \n",r2->toValue());
}
