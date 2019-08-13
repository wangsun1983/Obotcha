#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Sha.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

using namespace obotcha;

int test_sha512() {
    
    Sha sha1 = createSha(SHA_512);
    //String encrypt(String str);
    while(1) {
        String s = createString("hello world");
        String s1 = sha1->encrypt(s);
        if(s1 == nullptr ||s1->size() <=0) {
            printf("---[TestSha Test {Sha512:encrypt(String)} case1] [FAILED]--- \n");
            break;
        }

        printf("---[TestSha Test {Sha512:encrypt(String)} case1] [Success]--- \n");
        break;
    }


    //String encrypt(File);
    while(1) {
        File f = createFile("test_data.file");
        String s1 = sha1->encrypt(f);
        if(s1 == nullptr ||s1->size() <=0) {
            printf("---[TestSha Test {Sha512:encrypt(File)} case1] [FAILED]--- \n");
            break;
        }

        if(!s1->equals("44a83ca8ef452824c8e0e1fab98f30e1303ef71642f8c48104713a6cce84a721c5f2174be0b03071adef4205edcb8048ceb0f900a10cc7a28e752e181b5eec8a")) {
            printf("---[TestSha Test {Sha512:encrypt(File)} case2] [FAILED]--- \n");
            break;
        }

        printf("---[TestSha Test {Sha512:encrypt(File)} case3] [Success]--- \n");
        break;
    }


    //ByteArray encryptRawData(ByteArray);
    while(1) {
        ByteArray data = createByteArray(64);
        for(int i = 0;i<64;i++) {
            data->fill(i,i);
        }

        ByteArray s1 = sha1->encryptRawData(data);
        if(s1 == nullptr ||s1->size() <=0) {
            printf("---[TestSha Test {Sha512:encryptRawData(ByteArray)} case1] [FAILED]--- \n");
            break;
        }

        printf("---[TestSha Test {Sha512:encryptRawData(ByteArray)} case2] [Success]--- \n");
        break;
    }
}
