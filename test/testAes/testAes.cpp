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

    test_aes_key_gen();

    test_aes_key_load();

    test_aes_ecb();

    test_aes_cbc();
}
