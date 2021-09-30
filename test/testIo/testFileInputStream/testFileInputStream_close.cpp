#include <stdio.h>

#include "File.hpp"
#include "FileInputStream.hpp"
#include "FileNotFoundException.hpp"
#include "Md.hpp"

using namespace obotcha;

void testFileInputStreamClose() {
  while(1) {
    int fd = open("./tmp/data.txt",O_RDONLY);
    {
      FileInputStream stream = createFileInputStream(fd);
      stream->open();
    }

    char data[1024];
    int len = read(fd,data,1024);
    if(len != 1024) {
      printf("---testFileInputStreamClose test1 [FAILED]---,len is %d \n",len);
    }
    break;
  }

  while(1) {
    int fd = open("./tmp/data.txt",O_WRONLY);
    {
      FileInputStream stream = createFileInputStream(fd);
      stream->close();
    }

    char data[1024];
    int len = read(fd,data,1024);
    if(len != -1) {
      printf("---testFileInputStreamClose test1 [FAILED]--- ,len is %d\n",len);
    }
    break;
  }
  printf("---testFileInputStreamClose test100 [OK]--- \n");
}
