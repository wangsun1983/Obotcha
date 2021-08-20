#include <stdio.h>

#include "File.hpp"
#include "FileInputStream.hpp"
#include "FileNotFoundException.hpp"
#include "Md.hpp"

using namespace obotcha;

void testFileInputStreamRead() {
  while(1) {
    File f = createFile("data.txt");

    FileInputStream stream = createFileInputStream(f);
    stream->open();

    File f2 = createFile("read_case1.txt");
    f2->removeAll();

    int fd = open("read_case1.txt",O_CREAT|O_WRONLY|O_APPEND,0666);
    while(1) {
        ByteArray data = stream->read(32*1024);
        if(data == nullptr) {
          break;
        }
        write(fd,data->toValue(),data->size());
    }
    
    close(fd);

    Md md5 = createMd();
    String v1 = md5->encrypt(createFile("data.txt"));
    String v2 = md5->encrypt(createFile("read_case1.txt"));
    if(v1 != v2) {
      printf("---testFileInputStreamRead test1 [FAILED]--- \n");
      break;
    }
    break;
  }
  printf("---testFileInputStreamRead test100 [OK]--- \n");
}
