#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Sha.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

using namespace obotcha;

int main() {
    Sha sha1 = createSha(AbstractSHA1);
    String abc = "hello world";
    String result = sha1->encrypt(abc);
    printf("sha1 is %s \n",result->toChars());
}
