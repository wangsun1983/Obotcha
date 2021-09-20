#include <execinfo.h>
#include <fcntl.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/types.h>
#include <unistd.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Exception.hpp"
#include "String.hpp"

namespace obotcha {

void _translateException(char *buff, const char *err) {
    char errormsg[256];
    sprintf(errormsg, "[Info]:%s \n----------END-----------\n\n", err);
    strcat(buff, errormsg);
}

void _translateException(char *buff, String err) {
    char errormsg[256];
    sprintf(errormsg, "[Info]:%s \n----------END-----------\n\n",
            err->toChars());
    strcat(buff, errormsg);
}

Exception::Exception(const char *v) { mErrInfo = createString(v); }

Exception::Exception(String v) { mErrInfo = v; }

String Exception::getErrInfo() { return mErrInfo; }

void Exception::printStack() {
    printf("-----------------[maps dump start]--------------- \n");
    const char *path = "/proc/self/maps";
    int fd = open(path, O_RDONLY);
    if (fd >= 0) {
        char buff[1024 * 256];
        read(fd, buff, 1024 * 256);
        close(fd);
        printf("%s \n", &buff[0]);
    }
    printf("-----------------[maps dump end]---------------- \n");
    printf("\n");
    printf("\n");

    printf("-----------------[stack dump start]-------------- \n");
    int size = 16;
    void *array[16];
    int stack_num = backtrace(array, size);
    char **stacktrace = backtrace_symbols(array, stack_num);
    for (int i = 0; i < stack_num; ++i) {
        printf("%s\n", stacktrace[i]);
    }
    printf("-----------------[stack dump end]--------------- \n");
    free(stacktrace);
}

} // namespace obotcha
