#include <stdio.h>
#include <unistd.h>

#include "HashSet.hpp"
#include "HashMap.hpp"

extern void testStackSize();
extern void testStackPush();

using namespace obotcha;

int main() {
    testStackPush();
    testStackSize();
    return 0;
}
