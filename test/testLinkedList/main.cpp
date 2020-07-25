#include <stdio.h>
#include <unistd.h>

#include "HashSet.hpp"
#include "HashMap.hpp"

using namespace obotcha;

extern int testLinkeListBase();
extern int testLinkeListQueue();

int main() {
    testLinkeListBase();
    testLinkeListQueue();
}
