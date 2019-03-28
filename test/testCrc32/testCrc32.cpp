#include <stdio.h>
#include "Crc32.hpp"

using namespace obotcha;

int main() {

    Crc32 cc = createCrc32();

    String abc = "helloworld";

    long value = cc->verify(abc);

    printf("value is %ld \n",value);

}
