#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "File.hpp"

using namespace obotcha;

int testCanRwx() {
    File readFile = createFile("readonly");
    File executeFile = createFile("executeonly");
    File writeFile = createFile("writeonly");

    //test read
    if(!readFile->canRead()) {
        printf("---[File Test {CanRead()} case1] [FAIL]--- \n");
    }

    if(executeFile->canRead()) {
        printf("---[File Test {CanRead()} case2] [FAIL]--- \n");
    }

    if(writeFile->canRead()) {
        printf("---[File Test {CanRead()} case2] [FAIL]--- \n");
    }

    //testwrite
    if(readFile->canWrite()) {
        printf("---[File Test {CanWrite()} case1] [FAIL]--- \n");
    }

    if(executeFile->canWrite()) {
        printf("---[File Test {CanWrite()} case2] [FAIL]--- \n");
    }

    if(!writeFile->canWrite()) {
        printf("---[File Test {CanWrite()} case2] [FAIL]--- \n");
    }

    //testexe
    if(readFile->canExecute()) {
        printf("---[File Test {canExecute()} case1] [FAIL]--- \n");
    }

    if(!executeFile->canExecute()) {
        printf("---[File Test {canExecute()} case2] [FAIL]--- \n");
    }

    if(writeFile->canExecute()) {
        printf("---[File Test {canExecute()} case2] [FAIL]--- \n");
    }

    printf("---[File Test {canRead/canWrite/canExecute()} case100] [OK]--- \n");

}
