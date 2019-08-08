#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Des.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

using namespace obotcha;

extern int test_des_ecb();
extern int test_des_cbc();

int main() {
#if 0
    Des des = createDes(DesTypeCBC);
    //des->genKey("abc_key");
    des->loadKey("abc_key");
    String abc = createString("hello world \n");
    String abc2 = createString("myabc is efg");
    ByteArray arrAbc2 = createByteArray(abc2);
    char *q = arrAbc2->toValue();
    printf("q is %s \n",q);

    ByteArray ret = des->encrypt(createByteArray(abc));
    ByteArray ret2 = des->decrypt(ret);
    char *p = ret2->toValue();
    printf("value is %s \n",p);
    des->encrypt("test_data.file","encrypt.file");
    printf("file trace1 \n");
    des->decrypt("encrypt.file","dencrypt.file");
    printf("file trace2 \n");
#endif
    printf("---[TestDes Test Start]--- \n");

    //void genKey(File);
    while(1) {
        File f = createFile("encrypt.file");
        Des des = createDes();
        if(f->exists()) {
            f->removeAll();
        }

        if(des->genKey(f) != 0) {
            printf("---[TestDes Test {genKey(File)} case1] [FAILED]--- \n");
            break;
        }

        if(!f->exists()) {
            printf("---[TestDes Test {genKey(File)} case2] [FAILED]--- \n");
            break;
        }

        if(f->length() <= 0) {
            printf("---[TestDes Test {genKey(File)} case3] [FAILED]--- \n");
            break;
        }

        f = createFile("/abc.txt");
        if(des->genKey(f) != -DesSaveKeyFail) {
            printf("---[TestDes Test {genKey(File)} case4] [FAILED]--- \n");
            break;
        }

        printf("---[TestDes Test {genKey(File)} case5] [Success]--- \n");
        break;
    }

    //genKey(String filepath)
    while(1) {
        String f = createString("encrypt.file");
        File file = createFile(f);

        Des des = createDes();
        if(file->exists()) {
            file->removeAll();
        }

        if(des->genKey(f) != 0) {
            printf("---[TestDes Test {genKey(String)} case1] [FAILED]--- \n");
            break;
        }

        if(!file->exists()) {
            printf("---[TestDes Test {genKey(String)} case2] [FAILED]--- \n");
            break;
        }

        if(file->length() <= 0) {
            printf("---[TestDes Test {genKey(String)} case3] [FAILED]--- \n");
            break;
        }

        f = createString("/abc.txt");
        if(des->genKey(f) != -DesSaveKeyFail) {
            printf("---[TestDes Test {genKey(String)} case4] [FAILED]--- \n");
            break;
        }

        printf("---[TestDes Test {genKey(String)} case5] [Success]--- \n");
        break;
    }

    //genKey(const char * filepath);
    while(1) {
        //String f = createString("encrypt.file");
        const char*f = "encrypt.file";
        File file = createFile(f);

        Des des = createDes();
        if(file->exists()) {
            file->removeAll();
        }

        if(des->genKey(f) != 0) {
            printf("---[TestDes Test {genKey(const char *)} case1] [FAILED]--- \n");
            break;
        }

        if(!file->exists()) {
            printf("---[TestDes Test {genKey(const char *)} case2] [FAILED]--- \n");
            break;
        }

        if(file->length() <= 0) {
            printf("---[TestDes Test {genKey(const char *)} case3] [FAILED]--- \n");
            break;
        }

        const char*f2 = "/abc.txt";
        if(des->genKey(f2) != -DesSaveKeyFail) {
            printf("---[TestDes Test {genKey(const char *)} case4] [FAILED]--- \n");
            break;
        }

        printf("---[TestDes Test {genKey(const char *)} case5] [Success]--- \n");
        break;
    }

    //genKey(File,String content);
    while(1) {
        //String f = createString("encrypt.file");
        const char*f = "encrypt.file";
        File file = createFile(f);
        String content = createString("content");

        Des des = createDes();
        if(file->exists()) {
            file->removeAll();
        }

        if(des->genKey(file,content) != 0) {
            printf("---[TestDes Test {genKey(File,String content)} case1] [FAILED]--- \n");
            break;
        }

        if(!file->exists()) {
            printf("---[TestDes Test {genKey(File,String content)} case2] [FAILED]--- \n");
            break;
        }

        if(file->length() <= 0) {
            printf("---[TestDes Test {genKey(File,String content)} case3] [FAILED]--- \n");
            break;
        }

        const char*f2 = "/abc.txt";
        File file2 = createFile(f2);
        if(des->genKey(file2,content) != -DesSaveKeyFail) {
            printf("---[TestDes Test {genKey(File,String content)} case4] [FAILED]--- \n");
            break;
        }

        printf("---[TestDes Test {genKey(File,String content)} case5] [Success]--- \n");
        break;
    }

    //genKey(String filepath,String content);
    while(1) {
        String filepath = createString("encrypt.file");
        File file = createFile(filepath);
        String content = createString("content");

        Des des = createDes();
        if(file->exists()) {
            file->removeAll();
        }

        if(des->genKey(filepath,content) != 0) {
            printf("---[TestDes Test {genKey(String filepath,String content)} case1] [FAILED]--- \n");
            break;
        }

        if(!file->exists()) {
            printf("---[TestDes Test {genKey(String filepath,String content)} case2] [FAILED]--- \n");
            break;
        }

        if(file->length() <= 0) {
            printf("---[TestDes Test {genKey(String filepath,String content)} case3] [FAILED]--- \n");
            break;
        }

        String f2 = "/abc.txt";        
        if(des->genKey(f2,content) != -DesSaveKeyFail) {
            printf("---[TestDes Test {genKey(String filepath,String content)} case4] [FAILED]--- \n");
            break;
        }

        printf("---[TestDes Test {genKey(String filepath,String content)} case5] [Success]--- \n");
        break;
    }

    //genKey(const char * filepath,String content);
    while(1) {
        String filepath = createString("encrypt.file");
        File file = createFile(filepath);
        String content = createString("content");

        Des des = createDes();
        if(file->exists()) {
            file->removeAll();
        }

        if(des->genKey("encrypt.file",content) != 0) {
            printf("---[TestDes Test {genKey(const char * filepath,String content)} case1] [FAILED]--- \n");
            break;
        }

        if(!file->exists()) {
            printf("---[TestDes Test {genKey(const char * filepath,String content)} case2] [FAILED]--- \n");
            break;
        }

        if(file->length() <= 0) {
            printf("---[TestDes Test {genKey(const char * filepath,String content)} case3] [FAILED]--- \n");
            break;
        }

        if(des->genKey("/abc.txt",content) != -DesSaveKeyFail) {
            printf("---[TestDes Test {genKey(const char * filepath,String content)} case4] [FAILED]--- \n");
            break;
        }

        printf("---[TestDes Test {genKey(const char * filepath,String content)} case5] [Success]--- \n");
        break;
    }

    //int loadKey(File);
    File f = createFile("key.file");
    f->createNewFile();
    Des des1 = createDes();
    des1->genKey(f);

    while(1) {
        Des des = createDes();
        
        File f1 = createFile("abc.file");
        if(des->loadKey(f1) != -DesNotExistFail) {
            printf("---[TestDes Test {loadKey(File)} case1] [FAILED]--- \n");
            break;
        }

        if(des->loadKey(f) != 0) {
            printf("---[TestDes Test {loadKey(File)} case2] [FAILED]--- \n");
            break;
        }

        printf("---[TestDes Test {loadKey(File)} case3] [Success]--- \n");
        break;
    }

    //int loadKey(String);
    while(1) {
        Des des = createDes();
        if(des->loadKey(createString("abc.file")) != -DesNotExistFail) {
            printf("---[TestDes Test {loadKey(String)} case1] [FAILED]--- \n");
            break;
        }

        if(des->loadKey(createString("key.file")) != 0) {
            printf("---[TestDes Test {loadKey(String)} case2] [FAILED]--- \n");
            break;
        }

        printf("---[TestDes Test {loadKey(String)} case3] [Success]--- \n");
        break;
    }

    //int loadKey(const char *);
    while(1) {
        Des des = createDes();
        if(des->loadKey("abc.file") != -DesNotExistFail) {
            printf("---[TestDes Test {loadKey(const char *)} case1] [FAILED]--- \n");
            break;
        }

        if(des->loadKey("key.file") != 0) {
            printf("---[TestDes Test {loadKey(const char *)} case2] [FAILED]--- \n");
            break;
        }

        printf("---[TestDes Test {loadKey(const char *)} case3] [Success]--- \n");
        break;
    }

    test_des_ecb();
    test_des_cbc();
}
