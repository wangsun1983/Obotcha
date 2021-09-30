#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "FileOutputStream.hpp"
#include "FileInputStream.hpp"
#include "File.hpp"

using namespace obotcha;

void fileoutput_trunc_test() {

    //bool _FileOutputStream::write(char c)
    while(1) {
        File file = createFile("./tmp/trucn_test1.txt");
        file->createNewFile();
        FileOutputStream stream = createFileOutputStream(file);
        stream->open(st(OutputStream)::Trunc);
        stream->write('a');
        stream->flush();
        stream->close();

        FileOutputStream stream2 = createFileOutputStream(file);
        stream2->open(st(OutputStream)::Trunc);
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

        //file->removeAll();

        printf("---[TestFileOutputStream Test {open(Trunc)} case3] [OK]--- \n");
        break;
    }

    while(1) {
        File file = createFile("./tmp/trucn_test2.txt");
        file->createNewFile();
        FileOutputStream stream = createFileOutputStream(file);
        stream->open(st(OutputStream)::Trunc);
        ByteArray data = createByteArray(12);
        for(int i = 0;i<12;i++) {
          data[i] = i;
        }

        stream->write(data,3,3);
        stream->flush();

        if(file->length() != 3) {
          printf("---[TestFileOutputStream Test {open(Trunc)} case4] [FAILED]---,len is %ld \n",file->length());
          break;
        }

        int fd = open("./tmp/trucn_test2.txt",O_RDONLY);
        byte readbuf[3];
        read(fd,readbuf,3);

        if(readbuf[0] != 3 || readbuf[1] != 4 || readbuf[2] != 5) {
          printf("---[TestFileOutputStream Test {open(Trunc)} case5] [FAILED]--- \n");
        }
        close(fd);

        printf("---[TestFileOutputStream Test {open(Trunc)} case6] [OK]--- \n");
        break;
    }

}
