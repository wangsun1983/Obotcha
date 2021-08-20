#include <stdio.h>

#include "File.hpp"
#include "FileInputStream.hpp"
#include "FileNotFoundException.hpp"
#include "Md.hpp"

using namespace obotcha;

void testFileInputStreamReadAll() {
  while(1) {
    File f = createFile("data.txt");
    FileInputStream stream = createFileInputStream(f);
    stream->open();

    ByteArray data = stream->readAll();

    int fd = open("read_all_case1.txt",O_CREAT|O_WRONLY|O_TRUNC,0666);
    write(fd,data->toValue(),data->size());
    close(fd);

    Md md5 = createMd();
    String v1 = md5->encrypt(createFile("data.txt"));
    String v2 = md5->encrypt(createFile("read_all_case1.txt"));
    if(v1 != v2) {
      printf("---testFileInputStreamReadAll test1 [FAILED]--- \n");
      break;
    }
    break;
  }
  printf("---testFileInputStreamReadAll test100 [OK]--- \n");
}
