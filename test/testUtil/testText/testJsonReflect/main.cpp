#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <functional>

#include "Integer.hpp"
#include "String.hpp"

using namespace obotcha;

extern void testImport();
extern void testReflect();
extern void testHashMapStringString();
extern void testArrayListString();
extern void testUserDataReflect();
extern void testInnerClassReflect();

int main() {
    //testReflect();
    //testImport();

    testInnerClassReflect();
    //testUserDataReflect();
    //testHashMapStringString();
    //testArrayListString();
}
