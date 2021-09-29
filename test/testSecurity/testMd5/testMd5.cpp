#include <stdio.h>

#include "Md.hpp"
#include "File.hpp"

using namespace obotcha;

int test_md5() {
    File f = createFile("test_data.file");
    // String encrypt(File);
    while(1) {
        Md md = createMd(MdType5);
        String result = md->encrypt(f);

        if(result == nullptr || result->size() == 0) {
            printf("---[TestMd5 Test {Md5:encrypt(File)} case1] [FAILED]--- \n");
            break;
        }
        
        if(!result->equals("b1203a74f727d920322d388b279c3b2c")) {
            printf("---[TestMd5 Test {Md5:encrypt(File)} case1] [FAILED]--- \n");
            break;
        }

        printf("---[TestMd5 Test {Md5:encrypt(File)} case2] [Success]--- \n");
        break;
          
    }

    //String encrypt(String);
    while(1) {
        Md md = createMd(MdType5);
        String str = createString("hello world");
        String result = md->encrypt(str);

        if(result == nullptr || result->size() == 0) {
            printf("---[TestMd5 Test {Md5:encrypt(String)} case1] [FAILED]--- \n");
            break;
        }

        printf("---[TestMd5 Test {Md5:encrypt(String)} case2] [Success]--- \n");
        break;          
    }

    return 0;
}
