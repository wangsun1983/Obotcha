#include <stdio.h>

#include "Md.hpp"
#include "File.hpp"

using namespace obotcha;

int test_md4() {
    File f = createFile("test_data.file");
    // String encrypt(File);
    while(1) {
        Md md = createMd(MdType4);
        String result = md->encrypt(f);

        if(result == nullptr || result->size() == 0) {
            printf("---[TestMd5 Test {Md4:encrypt(File)} case1] [FAILED]--- \n");
            break;
        }

        printf("---[TestMd5 Test {Md4:encrypt(File)} case2] [Success]--- \n");
        break;
          
    }

    //String encrypt(String);
    while(1) {
        Md md = createMd(MdType4);
        String str = createString("hello world");
        String result = md->encrypt(str);

        if(result == nullptr || result->size() == 0) {
            printf("---[TestMd5 Test {Md4:encrypt(String)} case1] [FAILED]--- \n");
            break;
        }

        printf("---[TestMd5 Test {Md4:encrypt(String)} case2] [Success]--- \n");
        break;          
    }

    return 0;
}
