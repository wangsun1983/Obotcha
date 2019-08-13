#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "FileOutputStream.hpp"
#include "FileInputStream.hpp"
#include "File.hpp"

using namespace obotcha;

int fileoutput_trunc_test();
int fileoutput_append_test();

int main() {
    //writeline
    printf("---[FileOutputStream Test Start]--- \n");

    //bool _FileOutputStream::write(char c)
    while(1) {
        File file = createFile("abc.txt");
        FileOutputStream stream = createFileOutputStream(file);
        stream->open(FileOpenType::Trunc);
        stream->write('a');
        stream->flush();
        stream->close();

        if(file->length() != 1) {
            printf("---[TestFileOutputStream Test {write(char)} case1] [FAILED]--- \n");
            break;
        }

        FileInputStream inputstream = createFileInputStream(file);
        inputstream->open();
        ByteArray content = inputstream->readAll();
        if(content == nullptr || content->size() != 1 ||content->at(0) != 'a') {
            printf("---[TestFileOutputStream Test {write(char)} case2] [FAILED]--- \n");
            break;
        }

        file->removeAll();

        printf("---[TestFileOutputStream Test {write(char)} case3] [Success]--- \n");
        break;
    }

    //bool _FileOutputStream::write(ByteArray buff)
    while(1) {
        File file = createFile("abc.txt");
        FileOutputStream stream = createFileOutputStream(file);
        stream->open(FileOpenType::Trunc);
        ByteArray b = createByteArray(createString("hello"));
        stream->write(b);
        stream->flush();
        stream->close();

        if(file->length() != 5) {
            printf("---[TestFileOutputStream Test {write(ByteArray)} case1] [FAILED]--- \n");
            break;
        }

        FileInputStream inputstream = createFileInputStream(file);
        inputstream->open();
        ByteArray content = inputstream->readAll();
        if(content == nullptr || content->size() != 5) {
            printf("---[TestFileOutputStream Test {write(ByteArray)} case2] [FAILED]--- \n");
            break;
        }

        String cc = content->toString();
        if(!cc->equals("hello")) {
            printf("---[TestFileOutputStream Test {write(ByteArray)} case3] [FAILED]--- \n");
            break;
        }

        file->removeAll();

        printf("---[TestFileOutputStream Test {write(ByteArray)} case4] [Success]--- \n");
        break;
    }

    //bool _FileOutputStream::write(ByteArray buff,long size)
    while(1) {
        File file = createFile("abc.txt");
        FileOutputStream stream = createFileOutputStream(file);
        stream->open(FileOpenType::Trunc);

        ByteArray b = createByteArray(createString("helloworld"));
        stream->write(b,5);
        stream->flush();
        stream->close();

        if(file->length() != 5) {
            printf("---[TestFileOutputStream Test {write(ByteArray,long)} case1] [FAILED]--- \n");
            break;
        }

        FileInputStream inputstream = createFileInputStream(file);
        inputstream->open();
        ByteArray content = inputstream->readAll();
        if(content == nullptr || content->size() != 5) {
            printf("---[TestFileOutputStream Test {write(ByteArray,long)} case2] [FAILED]--- \n");
            break;
        }

        String cc = content->toString();
        if(!cc->equals("hello")) {
            printf("---[TestFileOutputStream Test {write(ByteArray,long)} case3] [FAILED]--- \n");
            break;
        }

        file->removeAll();

        printf("---[TestFileOutputStream Test {write(ByteArray,long)} case4] [Success]--- \n");
        break;
    }

    //bool _FileOutputStream::writeString(String s)
    while(1) {
        File file = createFile("abc.txt");
        FileOutputStream stream = createFileOutputStream(file);
        stream->open(FileOpenType::Trunc);
        stream->writeString(createString("nihao,abc"));
        stream->flush();
        stream->close();

        if(file->length() != 9) {
            printf("---[TestFileOutputStream Test {write(String)} case1] [FAILED]--- \n");
            break;
        }

        FileInputStream inputstream = createFileInputStream(file);
        inputstream->open();
        ByteArray content = inputstream->readAll();
        if(content == nullptr || content->size() != 9) {
            printf("---[TestFileOutputStream Test {write(String)} case2] [FAILED]--- \n");
            break;
        }

        String cc = content->toString();
        if(!cc->equals("nihao,abc")) {
            printf("---[TestFileOutputStream Test {write(String)} case3] [FAILED]--- \n");
            break;
        }

        file->removeAll();

        printf("---[TestFileOutputStream Test {write(String)} case4] [Success]--- \n");
        break;
    }

    fileoutput_trunc_test();

    fileoutput_append_test();
}
