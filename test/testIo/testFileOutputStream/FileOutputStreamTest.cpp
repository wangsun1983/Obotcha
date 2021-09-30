#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "FileOutputStream.hpp"
#include "FileInputStream.hpp"
#include "File.hpp"

using namespace obotcha;

void fileoutput_base_test() {
    //writeline
    printf("---[FileOutputStream Test Start]--- \n");

    //bool _FileOutputStream::write(char c)
    while(1) {
        File file = createFile("./tmp/base_test_1.txt");
        file->createNewFile();
        FileOutputStream stream = createFileOutputStream(file);
        stream->open(st(OutputStream)::Trunc);
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

        //file->removeAll();

        printf("---[TestFileOutputStream Test {write(char)} case3] [OK]--- \n");
        break;
    }

    //bool _FileOutputStream::write(ByteArray buff)
    while(1) {
        File file = createFile("./tmp/base_test_2.txt");
        file->createNewFile();
        FileOutputStream stream = createFileOutputStream(file);
        stream->open(st(OutputStream)::Trunc);
        ByteArray b = createString("hello")->toByteArray();
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

        //file->removeAll();

        printf("---[TestFileOutputStream Test {write(ByteArray)} case4] [OK]--- \n");
        break;
    }

    //bool _FileOutputStream::write(ByteArray buff,long size)
    while(1) {
        File file = createFile("./tmp/base_test_3.txt");
        file->createNewFile();
        FileOutputStream stream = createFileOutputStream(file);
        stream->open(st(OutputStream)::Trunc);

        ByteArray b = createString("helloworld")->toByteArray();
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
        if(!cc->equals("world")) {
            printf("---[TestFileOutputStream Test {write(ByteArray,long)} case3] [FAILED]--- \n");
            break;
        }

        //file->removeAll();

        printf("---[TestFileOutputStream Test {write(ByteArray,long)} case4] [OK]--- \n");
        break;
    }

    //bool _FileOutputStream::writeString(String s)
    while(1) {
        File file = createFile("./tmp/base_test_4.txt");
        file->createNewFile();
        FileOutputStream stream = createFileOutputStream(file);
        stream->open(st(OutputStream)::Trunc);
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

        //file->removeAll();

        printf("---[TestFileOutputStream Test {write(String)} case4] [OK]--- \n");
        break;
    }
}
