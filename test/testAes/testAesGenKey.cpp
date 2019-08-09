#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Aes.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

using namespace obotcha;

int test_aes_key_gen() {

    //int genKey(String decKeyFile,String encKeyFile);
    while(1) {
        String decKeyFile = createString("test_dec_key");
        String encKeyFile = createString("test_enc_key");
        File decFile = createFile(decKeyFile);
        decFile->removeAll();

        File encFile = createFile(encKeyFile);
        encFile->removeAll();

        Aes aes = createAes();
        int result = aes->genKey(decKeyFile,encKeyFile);
        if(!decFile->exists() 
            || !encFile->exists() 
            || decFile->length() == 0 
            || encFile->length() == 0) {

            printf("---[TestAes Test {Aes:genKey(String,String)} case1] [FAILED]--- \n");
            break;
        }
        
        printf("---[TestAes Test {Aes:genKey(String,String)} case2] [Success]--- \n");
        break;
    }

    //int genKey(String decKeyFile,String encKeyFile,String content);
    while(1) {
        String decKeyFile = createString("test_dec_key");
        String encKeyFile = createString("test_enc_key");
        File decFile = createFile(decKeyFile);
        decFile->removeAll();

        File encFile = createFile(encKeyFile);
        encFile->removeAll();

        Aes aes = createAes();
        int result = aes->genKey(decKeyFile,encKeyFile,createString("helloworld"));
        if(!decFile->exists() 
            || !encFile->exists() 
            || decFile->length() == 0 
            || encFile->length() == 0) {

            printf("---[TestAes Test {Aes:genKey(String,String,String)} case1] [FAILED]--- \n");
            break;
        }
        
        printf("---[TestAes Test {Aes:genKey(String,String,String)} case2] [Success]--- \n");
        break;
    }
    
    return 0;
}
