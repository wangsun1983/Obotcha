#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Sha.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

using namespace obotcha;

int test_sha256() {
    
    Sha sha1 = createSha(SHA_256);
    //String encrypt(String str);
    while(1) {
        String s = createString("hello world");
        String s1 = sha1->encrypt(s);
        if(s1 == nullptr ||s1->size() <=0) {
            printf("---[TestSha Test {Sha256:encrypt(String)} case1] [FAILED]--- \n");
            break;
        }

        printf("---[TestSha Test {Sha256:encrypt(String)} case1] [Success]--- \n");
        break;
    }


    //String encrypt(File);
    while(1) {
        File f = createFile("test_data.file");
        String s1 = sha1->encrypt(f);
        if(s1 == nullptr ||s1->size() <=0) {
            printf("---[TestSha Test {Sha256:encrypt(File)} case1] [FAILED]--- \n");
            break;
        }

        if(!s1->equals("6fc8ed2e78684172d2eb63bfd25879622632c1d250307b3b0fbd7574cba8df25")) {
            printf("---[TestSha Test {Sha256:encrypt(File)} case2] [FAILED]--- \n");
            break;
        }

        printf("---[TestSha Test {Sha256:encrypt(File)} case3] [Success]--- \n");
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
            printf("---[TestSha Test {Sha256:encryptRawData(ByteArray)} case1] [FAILED]--- \n");
            break;
        }

        printf("---[TestSha Test {Sha256:encryptRawData(ByteArray)} case2] [Success]--- \n");
        break;
    }
}
