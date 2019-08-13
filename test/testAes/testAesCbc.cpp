#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Aes.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "FileInputStream.hpp"

using namespace obotcha;

int test_aes_cbc() {

    String decKeyFile = createString("test_dec_key");
    String encKeyFile = createString("test_enc_key");
    File decFile = createFile(decKeyFile);
    decFile->removeAll();

    File encFile = createFile(encKeyFile);
    encFile->removeAll();

    Aes aes1 = createAes(AesTypeCBC);
    aes1->genKey(decKeyFile,encKeyFile);

    //encrypt(ByteArray buff)/decrypt(ByteArray buff)
    while(1) {
        Aes aes = createAes(AesTypeCBC);
        aes->loadKey(decFile,AesDecrypt);
        aes->loadKey(encFile,AesEncrypt);

        ByteArray testData = createByteArray(64);
        for(int i = 0;i<64;i++) {
            testData->fill(i,i);
        }

        ByteArray encData = aes->encrypt(testData);
        ByteArray decData = aes->decrypt(encData);

        if(decData == nullptr || decData->size() != testData->size()) {
            printf("---[TestAes Cbc Test {Aes:decrypt(ByteArray)/encrypt(ByteArray)} case1] [FAILED]--- \n");
            break;
        }

        int size = testData->size();
        for(int i = 0;i<size;i++) {
            if(testData->at(i) != decData->at(i)) {
                printf("---[TestAes Cbc Test {Aes:decrypt(ByteArray)/encrypt(ByteArray)} case2] [FAILED]--- \n");
                break;
            }
        }

        printf("---[TestAes Cbc Test {Aes:decrypt(ByteArray)/encrypt(ByteArray)} case3] [Success]--- \n");
        break;
    }

    //encrypt(File src,File des)/decrypt(File src,File des)
    while(1) {
        Aes aes = createAes(AesTypeCBC);
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
            printf("---[TestAes Cbc Test {Aes:decrypt(File,File)/encrypt(File,File)} case1] [FAILED]--- \n");
            break;
        }

        FileInputStream testFileStream = createFileInputStream(testFile);
        testFileStream->open();
        ByteArray testArr = testFileStream->readAll();


        FileInputStream testdecFileStream = createFileInputStream(decFile);
        testdecFileStream->open();
        ByteArray testdecArr = testdecFileStream->readAll();

        if(testArr->size() != testdecArr->size()) {
            printf("---[TestAes Cbc Test {Aes:decrypt(File,File)/encrypt(File,File)} case2] [FAILED]--- \n");
            break;
        }

        //int size = testArr->size();
        //for(int i = 0;i<size;i++) {
        //    printf("testArr[%d] is %d,testdecArr[%d] is %d \n",i,testArr->at(i),i,testdecArr->at(i));
            //if(testArr->at(i) != testdecArr->at(i)) {
            //    printf("---[TestAes Cbc Test {Aes:decrypt(File,File)/encrypt(File,File)} case3] [FAILED]--- \n");
            //    break;
            //}
        //}

        printf("---[TestAes Cbc Test {Aes:decrypt(File,File)/encrypt(File,File)} case4] [Success]--- \n");
        break;
    }
    
    return 0;
}
