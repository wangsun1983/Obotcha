#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Rsa.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

using namespace obotcha;

int main() {
    Rsa rsa = createRsa();
    //rsa->genKey("pub_k","priv_k");
    rsa->loadPublicKey("pub_k");
}
