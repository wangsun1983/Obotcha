#include <stdio.h>
#include <unistd.h>

#include "HashSet.hpp"
#include "HashMap.hpp"

using namespace obotcha;

extern int testHashAdd();
extern int testHashIteratorRemove();
extern int testHashContains();

int main() {
    testHashAdd();
    testHashIteratorRemove();
    testHashContains();
}
