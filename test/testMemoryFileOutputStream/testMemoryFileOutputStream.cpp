#include <stdio.h>

#include "MemoryFileOutputStream.hpp"

using namespace obotcha;

int main() {

    printf("---[MemoryFileOutputStream Test Start]--- \n");


    //_MemoryFileOutputStream(MemoryFile file);
    while(1) {
        MemoryFile file = createMemoryFile(createString("abc.txt"));
        MemoryFileOutputStream stream = createMemoryFileOutputStream(file);
        if(stream == nullptr) {
            printf("---[MemoryFileInputStream Test {Construct(MemoryFile)} case1] [FAIL]--- \n");
            break;
        }

        printf("---[MemoryFileInputStream Test {Construct(MemoryFile)} case2] [Success]--- \n");
        break;
    }

    //_MemoryFileOutputStream(String path);
    while(1) {
        MemoryFileOutputStream stream = createMemoryFileOutputStream(createString("abc.txt"));
        if(stream == nullptr) {
            printf("---[MemoryFileInputStream Test {Construct(String)} case1] [FAIL]--- \n");
            break;
        }

        printf("---[MemoryFileInputStream Test {Construct(String)} case2] [Success]--- \n");
        break;
    }

    /*
    bool write(char c);
    
    //bool write(char *buffer,int size);
    long write(ByteArray buff);

    long write(ByteArray buff,long size);

    bool writeString(String s);
    
    //no use
    bool open(FileOpenType opentype);

    bool open(long mapsize);

    bool open();
    
    void close();

    void flush();
    */


#if 0    
    MemoryFileOutputStream output = createMemoryFileOutputStream(createString("test_data.file"));
    output->open();
    //ByteArray v = input->readAll();
    String content = createString("hello world");
    output->writeString(content);

    //printf("value is %s \n",v->toValue());
#endif    
    return 1;
}
