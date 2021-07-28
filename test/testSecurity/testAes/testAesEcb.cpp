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
        String content = createString("hello world,i am hahahahah");
        ByteArray data1 = aes->encrypt(createByteArray(content));
        ByteArray data2 = aes->decrypt(data1);
        //printf("data1 size is %d,data2 size is %d ,content size is %d\n",data1->size(),data2->size(),content->size());

        String str2 = data2->toString();

        if(data2 == nullptr || !str2->equals("hello world,i am hahahahah")) {
            //if(str2 == nullptr) {
            //    printf("str2 is nullptr \n");
            //} else {
            //    printf("str2 is %s,str2 size is %d \n",str2->toChars(),str2->size());
            //}
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
            //if(decData == nullptr) {
            //    printf("decData is null!!!! \n");
            //} else {
            //    printf("decData size is %d,testData size is %d,encData size is %d \n",decData->size(),testData->size(),encData->size());
            //}
            printf("---[TestAes Ecb Test {Aes:decrypt(ByteArray)/encrypt(ByteArray)} case1] [FAILED]--- \n");
            break;
        }

        //int size = testData->size();
        //for(int i = 0;i<size;i++) {
        //    printf("testData[%d] is %d,decData[%d] is %d,encData[%d] is %d \n",i,testData->at(i),i,decData->at(i),i,encData->at(i));
        //    if(testData->at(i) != decData->at(i)) {
                //printf("---[TestAes Ecb Test {Aes:decrypt(ByteArray)/encrypt(ByteArray)} case2] [FAILED]--- \n");
                //break;
        //    }
        //}

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

        //int size = testArr->size();
        //for(int i = 0;i<size;i++) {
        //    if(testArr->at(i) != testdecArr->at(i)) {
        //        printf("---[TestAes Ecb Test {Aes:decrypt(File,File)/encrypt(File,File)} case3] [FAILED]--- \n");
        //        break;
        //    }
        //}

        printf("---[TestAes Ecb Test {Aes:decrypt(File,File)/encrypt(File,File)} case4] [Success]--- \n");
        break;
        
    }
    
    return 0;
}
