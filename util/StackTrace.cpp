#include "StackTrace.hpp"

namespace obotcha {

void _StackTrace::dumpStack(String tag) {
    printf("----------------------------------- \n");
    printf("Dump %s trace:",tag->toChars());
    int size = 16;
    void * array[16];
    int stack_num = backtrace(array, size);
    char ** stacktrace = backtrace_symbols(array, stack_num);
    for (int i = 0; i < stack_num; ++i) {
        printf("%s\n", stacktrace[i]);
    }
    printf("----------------------------------- \n");
    free(stacktrace);
}

}


