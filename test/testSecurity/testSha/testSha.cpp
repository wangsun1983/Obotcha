#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Sha.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

using namespace obotcha;

extern void test_sha1();
extern void test_sha224();
extern void test_sha256();
extern void test_sha384();
extern void test_sha512();

int main() {
    test_sha1();

    test_sha224();

    test_sha256();

    test_sha384();

    test_sha512();
}
