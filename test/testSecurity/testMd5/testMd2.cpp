#include <stdio.h>

#include "Md.hpp"
#include "File.hpp"

using namespace obotcha;

int test_md2() {
    File f = createFile("test_data.file");
    // String encrypt(File);
    while(1) {
        Md md = createMd(MdType2);
        String result = md->encrypt(f);
#ifndef OPENSSL_NO_MD2
        if(result != nullptr) {
            printf("---[TestMd5 Test {Md2:encrypt(File)} case1] [FAILED]--- \n");
            break;
        }
#else
        if(result == nullptr || result->size() == 0) {
            printf("---[TestMd5 Test {Md2:encrypt(File)} case1] [FAILED]--- \n");
            break;
        }
#endif  
        printf("---[TestMd5 Test {Md2:encrypt(File)} case2] [Success]--- \n");
        break;
          
    }

    //String encrypt(String);
    while(1) {
        Md md = createMd(MdType2);
        String str = createString("hello world");
        String result = md->encrypt(str);
#ifndef OPENSSL_NO_MD2
        if(result != nullptr) {
            printf("---[TestMd5 Test {Md2:encrypt(String)} case1] [FAILED]--- \n");
            break;
        }
#else
        if(result == nullptr || result->size() == 0) {
            printf("---[TestMd5 Test {Md2:encrypt(String)} case1] [FAILED]--- \n");
            break;
        }
#endif  
        printf("---[TestMd5 Test {Md2:encrypt(String)} case2] [Success]--- \n");
        break;
          
    }

    return 0;
}
