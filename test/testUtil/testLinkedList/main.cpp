#include <stdio.h>
#include <unistd.h>

#include "HashSet.hpp"
#include "HashMap.hpp"

using namespace obotcha;

extern int testLinkeListBase();
extern int testLinkeListQueue();
extern int testPutFirst();
extern int testPutLast();
extern int testTakeLast();
extern int testTakeFirst();
extern void testLinkedListRemoveAt();
extern void testLinkedListRemove();

int main() {
#if 0
    testLinkeListBase();
    testLinkeListQueue();
    testPutFirst();
    testPutLast();
    testTakeLast();
    testTakeFirst();
#endif
    testLinkedListRemoveAt();
    testLinkedListRemove();
    return 0;
}
