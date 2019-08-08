#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Des.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "FileInputStream.hpp"

using namespace obotcha;

int test_des_ecb() {
    Des des1 = createDes(DesTypeECB);
    File keyFile = createFile("TestEcbKey.file");
    if(keyFile->exists()) {
        keyFile->removeAll();
    }
    des1->genKey(keyFile);

    //String encrypt(String str)/ String decrypt(String str);
    while(1) {
        Des des = createDes(DesTypeECB);
        String testString = "hello world";
        des->loadKey("TestEcbKey.file");
        String t1 = des->encrypt(testString);
        if(t1 == nullptr) {
            printf("---[TestDesEcb Test {encrypt(String)/decrypt(String)} case1] [FAILED]--- \n");
            break;
        }
        String t2 = des->decrypt(t1);
        if(t2 == nullptr) {
            printf("---[TestDesEcb Test {encrypt(String)/decrypt(String)} case2] [FAILED]--- \n");
            break;
        }

        if(!t2->equals("hello world")) {
            printf("---[TestDesEcb Test {encrypt(String)/decrypt(String)} case3] [FAILED]--- \n");
            break;
        }

        printf("---[TestDesEcb Test {encrypt(String)/decrypt(String)} case4] [Sucess]--- \n");
        break;
    }

    //encrypt(ByteArray)/ decrypt(ByteArray)
    while(1) {
        ByteArray data = createByteArray(128);
        for(int i=0;i<128;i++) {
            data->fill(0,i);
        }

        Des des = createDes(DesTypeECB);
        des->loadKey("TestEcbKey.file");
        ByteArray t1 = des->encrypt(data);
        if(t1 == nullptr) {
            printf("---[TestDesEcb Test {encrypt(ByteArray)/ decrypt(ByteArray)} case1] [FAILED]--- \n");
            break;
        }

        ByteArray t2 = des->decrypt(t1);
        if(t2 == nullptr) {
            printf("---[TestDesEcb Test {encrypt(ByteArray)/ decrypt(ByteArray)} case2] [FAILED]--- \n");
            break;
        }

        for(int i = 0;i<128;i++) {
            if(t2->at(i) != data->at(i)) {
                printf("---[TestDesEcb Test {encrypt(ByteArray)/ decrypt(ByteArray)} case3] [FAILED]--- \n");
                break;
            }
        }

        printf("---[TestDesEcb Test {encrypt(ByteArray)/decrypt(ByteArray)} case4] [Sucess]--- \n");
        break;
    }

    //void encrypt(File src,File des);void decrypt(File src,File des);
    while(1) {
        Des des = createDes(DesTypeECB);
        des->loadKey("TestEcbKey.file");
        File encryptfile = createFile("encrypt.file");
        File file = createFile("test_base_file.file");

        des->encrypt(file,encryptfile);

        if(!encryptfile->exists()) {
            printf("---[TestDesEcb Test {encrypt(File,File)/ decrypt(File,File)} case1] [FAILED]--- \n");
            break;
        }

        File decryptfile = createFile("decrypt.file");
        des->decrypt(encryptfile,decryptfile);
        if(!decryptfile->exists()) {
            printf("---[TestDesEcb Test {encrypt(File,File)/ decrypt(File,File)} case2] [FAILED]--- \n");
            break;
        }

        FileInputStream encryptfileStream = createFileInputStream(file);
        encryptfileStream->open();
        ByteArray arr1 = encryptfileStream->readAll();
        //for(int index1 = 0;index1 < arr1->size();index1++) {
        //    printf("arr1[%d] is %d \n",index1,arr1->at(index1));
        //}

        FileInputStream decryptfileStream = createFileInputStream(decryptfile);
        decryptfileStream->open();
        ByteArray arr2 = decryptfileStream->readAll();
        //for(int index2 = 0;index2 < arr2->size();index2++) {
        //    printf("arr2[%d] is %d \n",index2,arr2->at(index2));
        //}

        if(arr1->size() != arr2->size()) {
            //printf("arr1 size is %d,arr2 size is %d \n",arr1->size(),arr2->size());
            printf("---[TestDesEcb Test {encrypt(File,File)/ decrypt(File,File)} case3] [FAILED]--- \n");
            break;
        }

        for(int i = 0;i<arr1->size();i++) {
            if(arr1->at(i) != arr2->at(i)) {
                printf("---[TestDesEcb Test {encrypt(File,File)/ decrypt(File,File)} case4] [FAILED]--- \n");
                break;
            }
        }

        printf("---[TestDesEcb Test {encrypt(File,File)/ decrypt(File,File)} case5] [Success]--- \n");
        break;
    }
}
