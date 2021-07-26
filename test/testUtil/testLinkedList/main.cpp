#include <stdio.h>
#include <unistd.h>

#include "HashSet.hpp"
#include "HashMap.hpp"

using namespace obotcha;

extern int testLinkeListBase();
extern int testLinkeListQueue();
extern int testEnqueueFirst();
extern int testEnqueueLast();
extern int testDequeueLast();
extern int testDequeueFirst();

int main() {
    testLinkeListBase();
    testLinkeListQueue();
    testEnqueueFirst();
    testEnqueueLast();
    testDequeueLast();
    testDequeueFirst();
}
