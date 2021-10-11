#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Object.hpp"

using namespace obotcha;

extern void testLinkParse();
extern void testLinkToString();

int main() {
    testLinkParse();
    testLinkToString();
    return 0;
}
