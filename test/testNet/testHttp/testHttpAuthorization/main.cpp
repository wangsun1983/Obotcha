#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Barrier.hpp"
#include "ByteArrayReader.hpp"

using namespace obotcha;

//https://www.jianshu.com/p/78faeb3a90e6

extern void testAuthorizationParse();
extern void testAuthorizationToString();

int main() {
    testAuthorizationParse();
    testAuthorizationToString();
    return 0;
}
