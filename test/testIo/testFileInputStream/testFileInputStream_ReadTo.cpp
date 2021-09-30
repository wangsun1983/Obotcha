#include <stdio.h>

#include "File.hpp"
#include "FileInputStream.hpp"
#include "FileNotFoundException.hpp"
#include "Md.hpp"

using namespace obotcha;

void testFileInputStreamReadTo() {
  while(1) {
    File f = createFile("./tmp/data.txt");

    FileInputStream stream = createFileInputStream(f);
    stream->open();

    File f2 = createFile("./tmp/read_to_case1.txt");
    f2->removeAll();

    int fd = open("./tmp/read_to_case1.txt",O_CREAT|O_WRONLY|O_APPEND,0666);
    ByteArray buff = createByteArray(32*1024);
    while(1) {
        int length = stream->readTo(buff);
        if(length == 0) {
          break;
        }
        write(fd,buff->toValue(),length);
    }

    close(fd);

    Md md5 = createMd();
    String v1 = md5->encrypt(createFile("./tmp/data.txt"));
    String v2 = md5->encrypt(createFile("./tmp/read_to_case1.txt"));
    if(v1 != v2) {
      printf("---testFileInputStreamReadTo test1 [FAILED]--- \n");
      break;
    }
    break;
  }
  printf("---testFileInputStreamReadTo test100 [OK]--- \n");
}
