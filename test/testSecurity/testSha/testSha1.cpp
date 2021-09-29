#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Sha.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

using namespace obotcha;

void test_sha1() {

    Sha sha1 = createSha(SHA_1);
    //String encrypt(String str);

    while(1) {
        String s = createString("hello world");
        String s1 = sha1->encrypt(s);
        if(s1 == nullptr ||s1->size() <=0) {
            printf("---[TestSha Test {Sha1:encrypt(String)} case1] [FAILED]--- \n");
            break;
        }

        printf("---[TestSha Test {Sha1:encrypt(String)} case1] [Success]--- \n");
        break;
    }


    //String encrypt(File);
    while(1) {
        File f = createFile("test_data.file");
        String s1 = sha1->encrypt(f);
        if(s1 == nullptr ||s1->size() <=0) {
            printf("---[TestSha Test {Sha1:encrypt(File)} case1] [FAILED]--- \n");
            break;
        }

        if(!s1->equals("87f46b278d51870d1b83f420f38438589250e4f5")) {
            printf("---[TestSha Test {Sha1:encrypt(File)} case2] [FAILED]--- \n");
            printf("s1 is %s \n",s1->toChars());
            break;
        }

        printf("---[TestSha Test {Sha1:encrypt(File)} case3] [Success]--- \n");
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
            printf("---[TestSha Test {Sha1:encryptRawData(ByteArray)} case1] [FAILED]--- \n");
            break;
        }

        printf("---[TestSha Test {Sha1:encryptRawData(ByteArray)} case2] [Success]--- \n");
        break;
    }
}
