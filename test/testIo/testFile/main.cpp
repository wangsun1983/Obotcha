#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "File.hpp"

extern void testFileGetName();
extern void testFileGetAbsPath();
extern void testCanRwx();
extern void testFileSetRwx();

int main() {

    testFileGetName();
    testFileGetAbsPath();
    testCanRwx();
    testFileSetRwx();
}
