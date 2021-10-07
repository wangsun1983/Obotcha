#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "File.hpp"

using namespace obotcha;

void testFileGetName() {
    File file;
    String name;

    //test1
    file = createFile("Obotcha/test/testFile/abc.cpp");
    name = file->getName();
    if(name == nullptr || !name->equals("abc.cpp")) {
      printf("---[File Test {getName()} case1] [FAIL]--- \n");
    }

    //test2
    file = createFile("Obotcha/test/testFile/abcdir/");
    name = file->getName();
    if(name == nullptr || !name->equals("abcdir")) {
      printf("---[File Test {getName()} case2] [FAIL]--- \n");
    }
    //test3
    file = createFile("abc11.cpp");
    name = file->getName();
    if(name == nullptr || !name->equals("abc11.cpp")) {
      printf("---[File Test {getName()} case3] [FAIL]--- \n");
    }

    printf("---[File Test {getName()} case100] [OK]--- \n");

}
