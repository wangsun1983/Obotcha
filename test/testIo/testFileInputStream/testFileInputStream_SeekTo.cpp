#include <stdio.h>

#include "File.hpp"
#include "FileInputStream.hpp"
#include "FileNotFoundException.hpp"
#include "Md.hpp"

using namespace obotcha;

void testFileInputStreamSeekTo() {
  while(1) {
    File f = createFile("./tmp/data.txt");

    FileInputStream stream = createFileInputStream(f);
    stream->open();

    File f2 = createFile("./tmp/read_to_case1.txt");
    f2->removeAll();

    int fd = open("./tmp/read_to_case1.txt",O_CREAT|O_WRONLY|O_APPEND,0666);
    stream->seekTo(1024*32);

    ByteArray buff = createByteArray(32*1024);
    while(1) {
        int length = stream->readTo(buff);
        if(length == 0) {
          break;
        }
        write(fd,buff->toValue(),length);
    }

    close(fd);

    long size1 = f2->length();
    long size0 = f->length();

    if(size1 != (size0-32*1024)) {
      printf("---testFileInputStreamSeekTo test1 [FAILED]--- \n");
    }

    FileInputStream stream2 = createFileInputStream(f);
    stream2->open();
    auto data = stream2->readAll();

    FileInputStream stream3 = createFileInputStream(f2);
    stream3->open();
    auto data2 = stream3->readAll();

    for(long i = 0; i < size1;i++) {
      if(data[i+32*1024] != data2[i]) {
        printf("---testFileInputStreamSeekTo test2 [FAILED]--- \n");
      }
    }

    //reset and test again
    stream->reset();
    File f3 = createFile("./tmp/read_to_case2.txt");
    f3->removeAll();

    fd = open("./tmp/read_to_case2.txt",O_CREAT|O_WRONLY|O_APPEND,0666);
    while(1) {
        int length = stream->readTo(buff);
        if(length == 0) {
          break;
        }
        write(fd,buff->toValue(),length);
    }

    Md md5 = createMd();
    String v3 = md5->encrypt(createFile("./tmp/data.txt"));
    String v4 = md5->encrypt(createFile("./tmp/read_to_case2.txt"));
    if(v3 != v4) {
      printf("---testFileInputStreamRead test4 [FAILED]--- \n");
      break;
    }

    break;
  }
  printf("---testFileInputStreamSeekTo test100 [OK]--- \n");
}
