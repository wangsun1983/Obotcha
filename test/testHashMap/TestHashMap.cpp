#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "HashMap.hpp"
#include "Integer.hpp"
#include "String.hpp"


extern void testHashMapString();
extern void testHashMapInteger();
extern void testHashMapDouble();
extern void testHashMapLong();
extern void testHashMapFloat();
extern void testHashMapBoolean();
extern void testHashMapObject();
extern void testHashMapInt();
extern void testHashMapSimpleBoolean();
extern void testHashMapSimpleDouble();
extern void testHashMapSimpleFloat();
extern void testHashMapSimpleLong();
extern void testHashMapSimpleString();

int main() {
    testHashMapString();
    testHashMapInteger();
    testHashMapDouble();
    testHashMapLong();
    testHashMapFloat();
    testHashMapBoolean();
    testHashMapObject();
    testHashMapInt();
    testHashMapSimpleBoolean();
    testHashMapSimpleDouble();
    testHashMapSimpleFloat();
    testHashMapSimpleLong();
    testHashMapSimpleString();
    return 0;
}
