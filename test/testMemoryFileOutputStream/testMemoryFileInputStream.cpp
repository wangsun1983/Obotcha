#include <stdio.h>

#include "MemoryFileOutputStream.hpp"

using namespace obotcha;

int main() {
    MemoryFileOutputStream output = createMemoryFileOutputStream(createString("test_data.file"));
    output->open();
    //ByteArray v = input->readAll();
    String content = createString("hello world");
    output->writeString(content);

    //printf("value is %s \n",v->toValue());
    return 1;
}
