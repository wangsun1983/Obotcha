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

int main() {
    testHashMapString();
    testHashMapInteger();
    testHashMapDouble();
    testHashMapLong();
    testHashMapFloat();
    testHashMapBoolean();
    testHashMapObject();
}
