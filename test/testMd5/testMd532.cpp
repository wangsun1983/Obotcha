#include <stdio.h>

#include "Md.hpp"
#include "File.hpp"

using namespace obotcha;

int main() {
    printf("MdType5 is %d \n",MdType5);
    Md cc = createMd(MdType4);
    printf("Md trace1 \n");
    String abc = "helloworld";
    printf("Md trace2 \n");

    String value = cc->encrypt(abc);

    printf("value is %s \n",value->toChars());

    File f = createFile("test_data.file");
    String value2 = cc->encrypt(f);
    printf("value2 is %s \n",value2->toChars());

}
