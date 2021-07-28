#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Aes.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

using namespace obotcha;

int test_aes_key_load() {

    String decKeyFile = createString("test_dec_key");
    String encKeyFile = createString("test_enc_key");
    File decFile = createFile(decKeyFile);
    decFile->removeAll();

    File encFile = createFile(encKeyFile);
    encFile->removeAll();
    
    Aes aes1 = createAes();
    aes1->genKey(decKeyFile,encKeyFile);

    //int loadKey(File,int);
    while(1) {
        Aes aes = createAes();
        int result = aes->loadKey(decFile,AesDecrypt);
        if(result != 0) {
            printf("---[TestAes Test {Aes:loadKey(File,int)} case1] [FAILED]--- \n");
            break;
        }

        result = aes->loadKey(encFile,AesDecrypt);
        if(result != 0) {
            printf("---[TestAes Test {Aes:loadKey(File,int)} case2] [FAILED]--- \n");
            break;
        }

        File errFile = createFile("tt");
        result = aes->loadKey(errFile,AesDecrypt);
        if(result == 0) {
            printf("---[TestAes Test {Aes:loadKey(File,int)} case3] [FAILED]--- \n");
            break;   
        }

        printf("---[TestAes Test {Aes:loadKey(File,int)} case4] [Success]--- \n");
        break;
    }

    //int loadKey(String,int);
    while(1) {
        Aes aes = createAes();
        int result = aes->loadKey(decKeyFile,AesDecrypt);
        if(result != 0) {
            printf("---[TestAes Test {Aes:loadKey(String,int)} case1] [FAILED]--- \n");
            break;
        }

        result = aes->loadKey(encKeyFile,AesDecrypt);
        if(result != 0) {
            printf("---[TestAes Test {Aes:loadKey(String,int)} case2] [FAILED]--- \n");
            break;
        }

        result = aes->loadKey(createString("tt"),AesDecrypt);
        if(result == 0) {
            printf("---[TestAes Test {Aes:loadKey(String,int)} case3] [FAILED]--- \n");
            break;   
        }

        printf("---[TestAes Test {Aes:loadKey(String,int)} case4] [Success]--- \n");
        break;
    }

    //int loadKey(const char *,int);
    while(1) {
        Aes aes = createAes();
        int result = aes->loadKey("test_dec_key",AesDecrypt);
        if(result != 0) {
            printf("---[TestAes Test {Aes:loadKey(const char *,int)} case1] [FAILED]--- \n");
            break;
        }

        result = aes->loadKey("test_enc_key",AesDecrypt);
        if(result != 0) {
            printf("---[TestAes Test {Aes:loadKey(const char *,int)} case2] [FAILED]--- \n");
            break;
        }

        result = aes->loadKey("tt",AesDecrypt);
        if(result == 0) {
            printf("---[TestAes Test {Aes:loadKey(const char *,int)} case3] [FAILED]--- \n");
            break;   
        }

        printf("---[TestAes Test {Aes:loadKey(const char *,int)} case4] [Success]--- \n");
        break;
    }
    
    return 0;
}
