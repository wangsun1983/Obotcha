#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Sha.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

using namespace obotcha;

void test_sha384() {

    Sha sha1 = createSha(SHA_384);
    //String encrypt(String str);
    while(1) {
        String s = createString("hello world");
        String s1 = sha1->encrypt(s);
        if(s1 == nullptr ||s1->size() <=0) {
            printf("---[TestSha Test {Sha384:encrypt(String)} case1] [FAILED]--- \n");
            break;
        }

        printf("---[TestSha Test {Sha384:encrypt(String)} case1] [Success]--- \n");
        break;
    }


    //String encrypt(File);
    while(1) {
        File f = createFile("test_data.file");
        String s1 = sha1->encrypt(f);
        if(s1 == nullptr ||s1->size() <=0) {
            printf("---[TestSha Test {Sha384:encrypt(File)} case1] [FAILED]--- \n");
            break;
        }

        if(!s1->equals("ff0c73130661d615b88cf0613e8689e30b83c2cc572c94825ba3ba2fc4a7a23f26ee28e90d1c496f9a2dd1ae7c431645")) {
            printf("---[TestSha Test {Sha384:encrypt(File)} case2] [FAILED]--- \n");
            break;
        }

        printf("---[TestSha Test {Sha384:encrypt(File)} case3] [Success]--- \n");
        break;
    }


    //ByteArray encryptRawData(ByteArray);
    while(1) {
        ByteArray data = createByteArray(64);
        for(int i = 0;i<64;i++) {
            data[i] = i;
        }

        ByteArray s1 = sha1->encryptRawData(data);
        if(s1 == nullptr ||s1->size() <=0) {
            printf("---[TestSha Test {Sha384:encryptRawData(ByteArray)} case1] [FAILED]--- \n");
            break;
        }

        printf("---[TestSha Test {Sha384:encryptRawData(ByteArray)} case2] [Success]--- \n");
        break;
    }
}
