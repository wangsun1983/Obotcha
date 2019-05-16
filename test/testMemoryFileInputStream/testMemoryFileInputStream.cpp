#include <stdio.h>

#include "MemoryFileInputStream.hpp"

using namespace obotcha;

int main() {
    MemoryFileInputStream input = createMemoryFileInputStream(createString("test_data.file"));
    input->open();
    ByteArray v = input->readAll();

    printf("value is %s \n",v->toValue());
    return 1;
}
