#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>
#include <sys/types.h>  
#include <sys/stat.h>
#include <fcntl.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

_Exception::_Exception(const char * v) {
    mErrInfo = createString(v);
}
    
_Exception::_Exception(String v) {
    mErrInfo = v;
}

_Exception::_Exception(int v) {
    mErrCode = v;
}

String _Exception::getErrInfo() {
    return mErrInfo;
}

int _Exception::getErrCode() {
    return mErrCode;
}

void _Exception::printStack() {
    printf("-----------------[maps dump start]--------------- \n");
    const char *path = "/proc/self/maps";
    int fd = open(path,O_RDONLY);
    if(fd >=0) {
        char buff[1024*256];
        read(fd,buff,1024*256);
        close(fd);
        printf("%s \n",&buff[0]);
    }
    printf("-----------------[maps dump end]---------------- \n");
    printf("\n");
    printf("\n");

    printf("-----------------[stack dump start]-------------- \n");
    int size = 16;
    void * array[16];
    int stack_num = backtrace(array, size);
    char ** stacktrace = backtrace_symbols(array, stack_num);
    for (int i = 0; i < stack_num; ++i) {
        printf("%s\n", stacktrace[i]);
    }
    printf("-----------------[stack dump end]--------------- \n");
    free(stacktrace);
}

}

