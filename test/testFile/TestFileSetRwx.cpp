#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "File.hpp"

using namespace obotcha;

int testFileSetRwx() {
    File file = createFile("setpropfle.data");
    //test1
    int value = file->setReadOnly();

    if(file->canWrite()) {
        printf("---[File Test {setReadOnly/setWriteOnle/SetExecuteOnly()} case1] [FAIL]--- \n");
    }

    if(file->canExecute()) {
        printf("---[File Test {setReadOnly/setWriteOnle/SetExecuteOnly()} case2] [FAIL]--- \n");
    }

    if(!file->canRead()) {
        printf("---[File Test {setReadOnly/setWriteOnle/SetExecuteOnly()} case3] [FAIL]--- \n");
    }

    //test2
    file->setWriteOnly();
    if(!file->canWrite()) {
        printf("---[File Test {setReadOnly/setWriteOnle/SetExecuteOnly()} case4] [FAIL]--- \n");
    }

    if(file->canExecute()) {
        printf("---[File Test {setReadOnly/setWriteOnle/SetExecuteOnly()} case5] [FAIL]--- \n");
    }

    if(file->canRead()) {
        printf("---[File Test {setReadOnly/setWriteOnle/SetExecuteOnly()} case6] [FAIL]--- \n");
    }

    //test3
    file->setExecuteOnly();
    if(file->canWrite()) {
        printf("---[File Test {setReadOnly/setWriteOnle/SetExecuteOnly()} case7] [FAIL]--- \n");
    }

    if(!file->canExecute()) {
        printf("---[File Test {setReadOnly/setWriteOnle/SetExecuteOnly()} case8] [FAIL]--- \n");
    }

    if(file->canRead()) {
        printf("---[File Test {setReadOnly/setWriteOnle/SetExecuteOnly()} case9] [FAIL]--- \n");
    }

    printf("---[File Test {setReadOnly/setWriteOnle/SetExecuteOnly()} case10] [FAIL]--- \n");

}
