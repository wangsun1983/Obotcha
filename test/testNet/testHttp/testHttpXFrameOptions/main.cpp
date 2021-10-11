#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Barrier.hpp"
#include "ByteArrayReader.hpp"

using namespace obotcha;

extern void testXFrameOptionsParse();
extern void testXFrameOptionsToString();

int main() {
    testXFrameOptionsParse();
    testXFrameOptionsToString();
    return 0;
}
