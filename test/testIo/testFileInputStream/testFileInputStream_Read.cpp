#include <stdio.h>

#include "File.hpp"
#include "FileInputStream.hpp"
#include "FileNotFoundException.hpp"
#include "Md.hpp"

using namespace obotcha;

void testFileInputStreamRead() {
  printf("testFileInputStreamRead trace1 \n");
  while(1) {
    File f = createFile("./tmp/data.txt");

    FileInputStream stream = createFileInputStream(f);
    stream->open();

    File f2 = createFile("./tmp/test_read.txt");
    f2->removeAll();

    int fd = open("./tmp/test_read.txt",O_CREAT|O_WRONLY|O_APPEND,0666);
    while(1) {
        ByteArray data = stream->read(32*1024);
        if(data == nullptr) {
          break;
        }
        write(fd,data->toValue(),data->size());
    }

    close(fd);

    Md md5 = createMd();
    String v1 = md5->encrypt(createFile("./tmp/data.txt"));
    String v2 = md5->encrypt(createFile("./tmp/test_read.txt"));
    if(v1 != v2) {
      printf("---testFileInputStreamRead test1 [FAILED]--- \n");
      break;
    }
    break;
  }
  printf("testFileInputStreamRead trace2 \n");
  while(1) {
    File f = createFile("./tmp/data.txt");

    FileInputStream stream = createFileInputStream(f);
    stream->open();

    File f2 = createFile("./tmp/test_read_by_bytearray.txt");
    f2->removeAll();

    int fd = open("./tmp/test_read_by_bytearray.txt",O_CREAT|O_WRONLY|O_APPEND,0666);
    ByteArray data = createByteArray(32*1024);

    while(1) {
        long len = stream->read(data);
        if(len == 0) {
          break;
        }
        write(fd,data->toValue(),len);
    }

    close(fd);

    Md md5 = createMd();
    String v1 = md5->encrypt(createFile("./tmp/data.txt"));
    String v2 = md5->encrypt(createFile("./tmp/test_read_by_bytearray.txt"));
    if(v1 != v2) {
      printf("---testFileInputStreamRead test2 [FAILED]--- \n");
      break;
    }
    break;
  }
  printf("testFileInputStreamRead trace3 \n");
  while(1) {
    File f = createFile("./tmp/data.txt");

    FileInputStream stream = createFileInputStream(f);
    stream->open();

    File f2 = createFile("./tmp/test_read_by_bytearray2.txt");
    f2->removeAll();

    int fd = open("./tmp/test_read_by_bytearray2.txt",O_CREAT|O_WRONLY|O_APPEND,0666);
    ByteArray data = createByteArray(32*1024);

    while(1) {
        long len = stream->read(data,1024);
        if(len == 0) {
          break;
        }
        write(fd,data->toValue()+1024,len);
    }

    close(fd);

    Md md5 = createMd();
    String v1 = md5->encrypt(createFile("./tmp/data.txt"));
    String v2 = md5->encrypt(createFile("./tmp/test_read_by_bytearray2.txt"));
    if(v1 != v2) {
      printf("---testFileInputStreamRead test3 [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---testFileInputStreamRead test100 [OK]--- \n");
}
