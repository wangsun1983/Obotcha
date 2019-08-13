#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "FileOutputStream.hpp"
#include "FileInputStream.hpp"
#include "File.hpp"

using namespace obotcha;

int fileoutput_trunc_test() {
    
    //bool _FileOutputStream::write(char c)
    while(1) {
        File file = createFile("abc.txt");
        FileOutputStream stream = createFileOutputStream(file);
        stream->open(FileOpenType::Trunc);
        stream->write('a');
        stream->flush();
        stream->close();

        FileOutputStream stream2 = createFileOutputStream(file);
        stream2->open(FileOpenType::Trunc);
        stream2->write('b');
        stream2->flush();
        stream2->close();

        if(file->length() != 1) {
            printf("---[TestFileOutputStream Test {open(Trunc)} case1] [FAILED]--- \n");
            break;
        }

        FileInputStream inputstream = createFileInputStream(file);
        inputstream->open();
        ByteArray content = inputstream->readAll();
        if(content == nullptr || content->size() != 1 ||content->at(0) != 'b') {
            printf("---[TestFileOutputStream Test {open(Trunc)} case2] [FAILED]--- \n");
            break;
        }

        file->removeAll();

        printf("---[TestFileOutputStream Test {open(Trunc)} case3] [Success]--- \n");
        break;
    }

    
}
