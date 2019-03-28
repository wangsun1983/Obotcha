#include <stdio.h>
#include "Md5.hpp"
#include "File.hpp"

using namespace obotcha;

int main() {

    Md5 cc = createMd5();

    String abc = "helloworld";

    String value = cc->verify(abc);

    printf("value is %s \n",value->toChars());

    File f = createFile("testMd532.cpp");
    String value2 = cc->verify(f);
    printf("value2 is %s \n",value2->toChars());

}
