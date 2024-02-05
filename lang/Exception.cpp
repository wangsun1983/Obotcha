/**
 * @file Exception.cpp
 * @brief The class Exception and its subclasses are a form of
 *        Throwable that indicates conditions that a reasonable
 *        application might want to catch.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-13
 * @license none
 */
#include <execinfo.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


#include "Exception.hpp"

namespace obotcha {

void Exception::printStack() const {
    printf("-----------------[maps dump start]--------------- \n");
    const char *path = "/proc/self/maps";
    if (int fd = open(path, O_RDONLY);fd >= 0) {
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
