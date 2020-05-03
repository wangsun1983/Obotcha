#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "File.hpp"

using namespace obotcha;

int testFileGetAbsPath() {
    File file;
    String name;

    //getCurrentpath
    char buff[256];
    char *p = getcwd(buff , 256);

    //test1
    file = createFile("abc.cpp");
    name = file->getAbsolutePath();
    if(name != nullptr ) {
      printf("---[File Test {getAbsolutePath()} case1] [FAIL]--- \n");
    }

    //test2
    file = createFile("makefile");
    name = file->getAbsolutePath();
    if(name == nullptr ) {
      printf("---[File Test {getAbsolutePath()} case2] [FAIL]--- \n");
    }

    char buff1[512];
    snprintf(buff1,512,"%s/%s",buff,"makefile");
    if(!name->equals(buff1)) {
        printf("---[File Test {getAbsolutePath()} case3] [FAIL]--- \n");
    }

    printf("---[File Test {getAbsolutePath()} case100] [OK]--- \n");
}
