#include <stdio.h>

#include "Md.hpp"
#include "File.hpp"

using namespace obotcha;

extern int test_md2();
extern int test_md4();
extern int test_md5();

int main() {
    printf("---[TestMd Test Start]--- \n");
    
    test_md2();
    test_md4();
    test_md5();

}
