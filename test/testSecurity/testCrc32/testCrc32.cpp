#include <stdio.h>
#include "Crc32.hpp"
#include "FileInputStream.hpp"

using namespace obotcha;

int main() {

    printf("---[TestCrc32 Test Start]--- \n");
    //testfile.data crc32 result is 82269724
    //encode(ByteArray b)
    long v1;
    long v2;
    long v3;

    while(1) {
        File f = createFile("testData.file");
        FileInputStream stream = createFileInputStream(f);
        stream->open();
        ByteArray array = stream->readAll();
        stream->close();
        Crc32 cc = createCrc32();
        v1 = cc->encode(array);
        if(v1 <= 0) {
            printf("---[TestCrc32 Test {encode(ByteArray)} case1] [FAILED]--- \n");
            break;
        }

        printf("---[TestCrc32 Test {encode(ByteArray)} case2] [Success]--- \n");
        break;
    }

    //encode(String)
    while(1) {
        File f = createFile("testData.file");
        FileInputStream stream = createFileInputStream(f);
        stream->open();
        ByteArray array = stream->readAll();
        stream->close();
        String str = array->toString();
        Crc32 cc = createCrc32();
        v2 = cc->encode(str);
        if(v2 <= 0) {
            printf("---[TestCrc32 Test {encode(String)} case1] [FAILED]--- \n");
            break;
        }

        printf("---[TestCrc32 Test {encode(String)} case2] [Success]--- \n");
        break;
    }


    //long encode(File);
    while(1) {
    	File f = createFile("testData.file");
        Crc32 cc = createCrc32();
        v3 = cc->encode(f);
        //printf("v is %ld \n",v);
        if(v3 <= 0) {
            printf("---[TestCrc32 Test {encode(File)} case1] [FAILED]--- \n");
            break;
        }

        printf("---[TestCrc32 Test {encode(File)} case2] [Success]--- \n");
        break;
    }

    if(v1 != v2 || v2!=v3 || v1!=v3) {
        printf("---[TestCrc32 Test {encode(File)} case3] [Fail]--- \n");
        printf("v1 = %ld,v2 = %ld,v3 = %ld \n",v1,v2,v3);
    }

    //Test More
#if 0    
    String Q1 = createString("abcdefghijklmn");
    Crc32 cc = createCrc32();
    ByteArray array = createByteArray(Q1);
    v1 = cc->encode(array);

    File f = createFile("testData2.file");
    Crc32 cc2 = createCrc32();
    v2 = cc2->encode(f);

    int size = array->size();
    for(int i = 0;i< size;i++) {
        printf("string array[%d] is %d \n",i,array->at(i));
    }

    FileInputStream stream = createFileInputStream(f);
    stream->open();
    ByteArray array2 = stream->readAll();
    int size2 = array2->size();
    for(int i = 0;i< size2;i++) {
        printf("file array[%d] is %d \n",i,array2->at(i));
    }
    
    printf("v1 is %ld,v2 is %ld \n",v1,v2);

    if(v1 != v2) {
        printf("---[TestCrc32 Test {encode(File)} case4] [Fail]--- \n");
    }
#endif    

}
