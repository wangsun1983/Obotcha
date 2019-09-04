#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#include "MemoryFileOutputStream.hpp"
#include "FileOutputStream.hpp"

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

    
    //bool write(char c);
    while(1) {
        MemoryFileOutputStream stream = createMemoryFileOutputStream(createString("abc.txt"));
        stream->open();
        if(!stream->write('a')) {
            printf("---[MemoryFileInputStream Test {write(char)} case1] [FAIL]--- \n");
            break;
        }
        stream->flush();
        stream->close();

        //check file
        int fd = open("abc.txt",O_RDONLY);
        char buff[32];
        read(fd,buff,1);
        if(buff[0] != 'a') {
            printf("---[MemoryFileInputStream Test {write(char)} case2] [FAIL]--- \n");
            break;
        }
        close(fd);

        //new file test
        MemoryFile newFile = createMemoryFile("new.txt");
        newFile->removeAll();
        stream = createMemoryFileOutputStream(newFile);
        stream->open();
        if(!stream->write('b')) {
            printf("---[MemoryFileInputStream Test {write(char)} case3] [FAIL]--- \n");
            break;
        }
        stream->flush();
        stream->close();

        //check file
        int fd2 = open("new.txt",O_RDONLY);
        char buff2[32];
        read(fd2,buff2,1);
        if(buff2[0] != 'b') {
            printf("---[MemoryFileInputStream Test {write(char)} case4] [FAIL]--- \n");
            break;
        }
        
        printf("---[MemoryFileInputStream Test {write(char)} case5] [Success]--- \n");
        break;
    }

    //long write(ByteArray buff);
    while(1) {
        MemoryFileOutputStream stream = createMemoryFileOutputStream(createString("abc.txt"));
        ByteArray buff = createByteArray(32);
        for(int i = 0;i < 32;i++) {
            buff->fill(i,'a' + i);
        }

        stream->open(32,Trunc);
        int writesize = stream->write(buff);
        stream->close();

        if(writesize != 32) {
            printf("---[MemoryFileInputStream Test {write(ByteArray)} case1] [FAIL]--- \n");
            break;
        }

        //check file
        int fd = open("abc.txt",O_RDONLY);
        char buff2[32];
        read(fd,buff2,32);
        for(int i = 0;i< 32;i++) {
            if(buff2[i] != buff->at(i)) {
                printf("---[MemoryFileInputStream Test {write(ByteArray)} case2] [FAIL]--- \n");
                break;
            }
        }
        close(fd);


        MemoryFileOutputStream stream3 = createMemoryFileOutputStream(createString("abc3.txt"));
        stream3->open(32,Trunc);
        if(stream3->write(nullptr) != -1) {
            printf("---[MemoryFileInputStream Test {write(ByteArray)} case3] [FAIL]--- \n");
            break;
        }

        printf("---[MemoryFileInputStream Test {write(ByteArray)} case4] [Success]--- \n");
        break;
    }

    //long write(ByteArray buff,long size);
    while(1) {
        File f = createFile("abc.txt");
        f->removeAll();

        MemoryFileOutputStream stream = createMemoryFileOutputStream(createString("abc.txt"));
        ByteArray buff = createByteArray(32);
        for(int i = 0;i < 32;i++) {
            buff->fill(i,'a' + i);
        }

        stream->open();

        int size = stream->write(buff,64);
        if(size != 32) {
            printf("---[MemoryFileInputStream Test {write(ByteArray,long)} case1] [FAIL]--- \n");
            break;
        }

        stream->close();

        //check file
        int fd = open("abc.txt",O_RDONLY);
        char buff2[32];
        read(fd,buff2,32);
        for(int i = 0;i< 32;i++) {
            if(buff2[i] != buff->at(i)) {
                printf("---[MemoryFileInputStream Test {write(ByteArray,long)} case2] [FAIL]--- \n");
                break;
            }
        }
        close(fd);

        MemoryFileOutputStream stream2 = createMemoryFileOutputStream(createString("abc.txt"));
        stream2->open();
        int size2 = stream2->write(buff,12);

        if(size2 != 12) {
            printf("---[MemoryFileInputStream Test {write(ByteArray,long)} case3] [FAIL]--- \n");
            break;
        }

        //check file
        int fd2 = open("abc.txt",O_RDONLY);
        char buff3[12];
        read(fd2,buff3,12);
        for(int i = 0;i< 12;i++) {
            if(buff3[i] != buff->at(i)) {
                printf("---[MemoryFileInputStream Test {write(ByteArray,long)} case4] [FAIL]--- \n");
                break;
            }
        }
        close(fd2);

        MemoryFileOutputStream stream3 = createMemoryFileOutputStream(createString("abc3.txt"));
        stream3->open(32,Trunc);
        if(stream3->write(nullptr,32) != -1) {
            printf("---[MemoryFileInputStream Test {write(ByteArray)} case5] [FAIL]--- \n");
            break;
        }

        printf("---[MemoryFileInputStream Test {write(ByteArray,long)} case6] [Success]--- \n");
        break;


    }

    //long writeString(String s);
    while(1) {
        File f = createFile("abc.txt");
        f->removeAll();

        MemoryFileOutputStream stream = createMemoryFileOutputStream(createString("abc.txt"));
        stream->open();
        String str = createString("hello world");
        long writesize = stream->writeString(str);
        if(writesize != str->size()) {
            printf("---[MemoryFileInputStream Test {writeString(String)} case1] [FAIL]--- \n");
            break;
        }
        stream->close();

        //check
        int fd2 = open("abc.txt",O_RDONLY);
        char buff3[str->size()];
        read(fd2,buff3,str->size());
        for(int i = 0;i< str->size();i++) {
            if(buff3[i] != str->toChars()[i]) {
                printf("---[MemoryFileInputStream Test {writeString(String)} case2] [FAIL]--- \n");
                break;
            }
        }
        close(fd2);

        stream = createMemoryFileOutputStream(createString("abc2.txt"));
        stream->open();
        
        long length2 = stream->writeString(nullptr);
        if(length2 != -1) {
            printf("---[MemoryFileInputStream Test {writeString(String)} case3] [FAIL]--- \n");
            break;
        }

        printf("---[MemoryFileInputStream Test {writeString(String)} case4] [Success]--- \n");
        break;

    }


    //bool open(FileOpenType opentype = Trunc);
    while(1) {
        File newFile = createFile("opentest.txt");
        newFile->removeAll();
        newFile->createNewFile();

        FileOutputStream filestream = createFileOutputStream(newFile);
        filestream->open();
        ByteArray array = createByteArray(8);
        for(int i = 0;i < 8;i++) {
            array->fill(i,'a' + i);
        }

        ByteArray array2 = createByteArray(2);
        for(int i = 0;i < 2;i++) {
            array->fill(i,'k' + i);
        }

        filestream->write(array);
        filestream->close();
        int fd = open("opentest.txt",O_RDONLY);
        char buff[8];
        read(fd,buff,8);
        for(int i = 0;i< 8;i++) {
            if(buff[i] != array->at(i)) {
                printf("---[MemoryFileInputStream Test {open(FileOpenType:Trunc)} case1] [FAIL]--- \n");
                break;
            }
        }
        close(fd);


        MemoryFileOutputStream stream = createMemoryFileOutputStream(createString("abc.txt"));
        stream->open(3,Trunc);
        long length = stream->write(array2);
        if(length != 2) {
            printf("---[MemoryFileInputStream Test {open(FileOpenType:Trunc)} case2] [FAIL]--- \n");
            break;
        }
        stream->close();

        fd = open("opentest.txt",O_RDONLY);
        char buff2[8];
        read(fd,buff2,8);
        if(buff2[0] != 'k' ||(buff2[1] != 'k'+1) 
            ||(buff2[2] != 'a'+2) || (buff2[3] != 'a' + 3) 
            ||(buff2[4] != 'a' + 4)) {
            printf("---[MemoryFileInputStream Test {open(FileOpenType:Trunc)} case3] [FAIL]--- \n");
            break;
        }

        printf("---[MemoryFileInputStream Test {open(FileOpenType:Trunc)} case4] [Success]--- \n");
        break;
    }

    //bool open(FileOpenType opentype = Append);
    while(1) {
        File newFile = createFile("opentest2.txt");
        newFile->removeAll();
        newFile->createNewFile();

        FileOutputStream filestream = createFileOutputStream(newFile);
        filestream->open();
        ByteArray array = createByteArray(8);
        for(int i = 0;i < 8;i++) {
            array->fill(i,'a' + i);
        }

        ByteArray array2 = createByteArray(2);
        for(int i = 0;i < 2;i++) {
            array2->fill(i,'k' + i);
        }

        filestream->write(array);
        filestream->close();
        int fd = open("opentest2.txt",O_RDONLY);
        char buff[8];
        read(fd,buff,8);
        for(int i = 0;i< 8;i++) {
            if(buff[i] != array->at(i)) {
                printf("---[MemoryFileInputStream Test {open(FileOpenType:Append)} case1] [FAIL]--- \n");
                break;
            }
        }
        close(fd);

        MemoryFileOutputStream stream = createMemoryFileOutputStream(createString("opentest2.txt"));

        stream->open(32,Append);
        
        long length = stream->write(array2);
        if(length != 2) {
            printf("---[MemoryFileInputStream Test {open(FileOpenType:Append)} case2] [FAIL]--- \n");
            break;
        }
        stream->close();

        fd = open("opentest2.txt",O_RDONLY);
        char buff2[11];
        read(fd,buff2,11);
        for(int i = 0;i< 8;i++) {
            //printf("buff2[%d] is %d,array[%d] is %d \n",i,buff2[i],i,array->at(i));
            if(buff2[i] != array->at(i)) {
                printf("---[MemoryFileInputStream Test {open(FileOpenType:Append)} case3] [FAIL]--- \n");
                break;
            }
        }

        if(buff2[8] != 'k' || (buff2[9] != 'k'+1) || (buff2[10] != 0)) {
            printf("---[MemoryFileInputStream Test {open(FileOpenType:Append)} case4] [FAIL]--- \n");
            break;
        }

        printf("---[MemoryFileInputStream Test {open(FileOpenType:Append)} case4] [Success]--- \n");
        break;
    }

    //bool open();
    while(1) {
        File newFile = createFile("opentest.txt");
        newFile->removeAll();
        newFile->createNewFile();

        FileOutputStream filestream = createFileOutputStream(newFile);
        filestream->open();
        ByteArray array = createByteArray(8);
        for(int i = 0;i < 8;i++) {
            array->fill(i,'a' + i);
        }

        ByteArray array2 = createByteArray(2);
        for(int i = 0;i < 2;i++) {
            array->fill(i,'k' + i);
        }

        filestream->write(array);
        filestream->close();
        int fd = open("opentest.txt",O_RDONLY);
        char buff[8];
        read(fd,buff,8);
        for(int i = 0;i< 8;i++) {
            if(buff[i] != array->at(i)) {
                printf("---[MemoryFileInputStream Test {open()} case1] [FAIL]--- \n");
                break;
            }
        }
        close(fd);


        MemoryFileOutputStream stream = createMemoryFileOutputStream(createString("abc.txt"));
        stream->open();
        long length = stream->write(array2);
        if(length != 2) {
            printf("---[MemoryFileInputStream Test {open()} case2] [FAIL]--- \n");
            break;
        }
        stream->close();

        fd = open("opentest.txt",O_RDONLY);
        char buff2[8];
        read(fd,buff2,8);
        if(buff2[0] != 'k' ||(buff2[1] != 'k'+1) 
            ||(buff2[2] != 'a'+2) || (buff2[3] != 'a' + 3) 
            ||(buff2[4] != 'a' + 4)) {
            printf("---[MemoryFileInputStream Test {open()} case3] [FAIL]--- \n");
            break;
        }

        printf("---[MemoryFileInputStream Test {open()} case4] [Success]--- \n");
        break;
    }
    
    return 1;
}
