#include <stdio.h>
#include <unistd.h>

#include "HashSet.hpp"
#include "HashMap.hpp"

using namespace obotcha;

extern void testHashAdd();
extern void testHashIteratorRemove();
extern void testHashContains();

int main() {
    testHashAdd();
    testHashIteratorRemove();
    testHashContains();
    return 0;
}
