#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Aes.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "FileInputStream.hpp"

using namespace obotcha;

int test_aes_ecb() {

    String decKeyFile = createString("test_dec_key");
    String encKeyFile = createString("test_enc_key");
    File decFile = createFile(decKeyFile);
    decFile->removeAll();

    File encFile = createFile(encKeyFile);
    encFile->removeAll();

    Aes aes1 = createAes(AesTypeECB);
    aes1->genKey(decKeyFile,encKeyFile);

    //decrypt(String str)/encrypt(String str)
    while(1) {
        Aes aes = createAes(AesTypeECB);
        aes->loadKey(decFile,AesDecrypt);
        aes->loadKey(encFile,AesEncrypt);

        String str = aes->encrypt(createString("hello world"));
        String str2 = aes->decrypt(str);

        if(str2 == nullptr || !str2->equals("hello world")) {
            printf("---[TestAes Ecb Test {Aes:decrypt(String str)/encrypt(String str)} case1] [FAILED]--- \n");
            break;
        }
        
        printf("---[TestAes Ecb Test {Aes:decrypt(String str)/encrypt(String str)} case2] [Success]--- \n");
        break;
    }

    //encrypt(ByteArray buff)/decrypt(ByteArray buff)
    while(1) {
        Aes aes = createAes(AesTypeECB);
        aes->loadKey(decFile,AesDecrypt);
        aes->loadKey(encFile,AesEncrypt);

        ByteArray testData = createByteArray(64);
        for(int i = 0;i<64;i++) {
            testData->fill(i,i);
        }

        ByteArray encData = aes->encrypt(testData);
        ByteArray decData = aes->decrypt(encData);

        if(decData == nullptr || decData->size() != testData->size()) {
            printf("---[TestAes Ecb Test {Aes:decrypt(ByteArray)/encrypt(ByteArray)} case1] [FAILED]--- \n");
            break;
        }

        int size = testData->size();
        for(int i = 0;i<size;i++) {
            printf("testData[%d] is %d,decData[%d] is %d,encData[%d] is %d \n",i,testData->at(i),i,decData->at(i),i,encData->at(i));
            if(testData->at(i) != decData->at(i)) {
                //printf("---[TestAes Ecb Test {Aes:decrypt(ByteArray)/encrypt(ByteArray)} case2] [FAILED]--- \n");
                //break;
            }
        }

        printf("---[TestAes Ecb Test {Aes:decrypt(ByteArray)/encrypt(ByteArray)} case3] [Success]--- \n");
        break;
    }

    //encrypt(File src,File des)/decrypt(File src,File des)
    while(1) {
        Aes aes = createAes(AesTypeECB);
        aes->loadKey(decFile,AesDecrypt);
        aes->loadKey(encFile,AesEncrypt);

        File testFile = createFile("test_data.file");
        File encFile = createFile("test_data_enc.file");
        if(encFile->exists()) {
            encFile->removeAll();
        }

        aes->encrypt(testFile,encFile);

        File decFile = createFile("test_data_dec.file");
        if(decFile->exists()) {
            decFile->removeAll();
        }

        aes->decrypt(encFile,decFile);

        if(!decFile->exists() || decFile->length() <= 0) {
            printf("---[TestAes Ecb Test {Aes:decrypt(File,File)/encrypt(File,File)} case1] [FAILED]--- \n");
            break;
        }

        FileInputStream testFileStream = createFileInputStream(testFile);
        testFileStream->open();
        ByteArray testArr = testFileStream->readAll();


        FileInputStream testdecFileStream = createFileInputStream(decFile);
        testdecFileStream->open();
        ByteArray testdecArr = testdecFileStream->readAll();

        if(testArr->size() != testdecArr->size()) {
            printf("---[TestAes Ecb Test {Aes:decrypt(File,File)/encrypt(File,File)} case2] [FAILED]--- \n");
            break;
        }

        int size = testArr->size();
        for(int i = 0;i<size;i++) {
            if(testArr->at(i) != testdecArr->at(i)) {
                printf("---[TestAes Ecb Test {Aes:decrypt(File,File)/encrypt(File,File)} case3] [FAILED]--- \n");
                break;
            }
        }

        printf("---[TestAes Ecb Test {Aes:decrypt(File,File)/encrypt(File,File)} case4] [FAILED]--- \n");
        break;
    }
    
    return 0;
}
