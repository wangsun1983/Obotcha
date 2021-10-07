#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Barrier.hpp"
#include "ByteArrayReader.hpp"

using namespace obotcha;

extern void testByteArrayLittleEndian();
extern void testByteArrayBigEndian();
extern void testByteArrayWriterArray();
extern void testByteArrayWriterString();
extern void testByteArrayWriterGet();

int main() {
    testByteArrayWriterGet();
    testByteArrayWriterString();
    testByteArrayWriterArray();
    testByteArrayBigEndian();
    testByteArrayLittleEndian();
    return 0;
}
