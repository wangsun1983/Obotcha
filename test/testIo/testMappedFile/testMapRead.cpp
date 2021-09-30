#include <stdio.h>

#include "File.hpp"
#include "FileInputStream.hpp"
#include "FileOutputStream.hpp"
#include "FileNotFoundException.hpp"
#include "System.hpp"
#include "MappedFile.hpp"

using namespace obotcha;

void testMapRead() {
    int fd = open("./tmp/abc.txt",O_CREAT | O_RDWR | O_TRUNC,S_IRUSR | S_IWUSR);
    char *txt = "hello world,this is a mapped file test";
    write(fd,txt,strlen(txt));
    close(fd);

    while(1) {
      MappedFile f = createMappedFileBuilder("./tmp/abc.txt")->setSize(256)->create();
      ByteArray data = f->getData();
      String str = data->toString();
      if(!str->equals(txt)) {
        printf("---[TestMappedFile read case1] [FAILED]--- \n");
        break;
      }

      fd = open("./tmp/abc.txt",O_CREAT | O_RDWR | O_TRUNC,S_IRUSR | S_IWUSR);
      char *tt = "write again";
      write(fd,tt,strlen(tt));

      str = data->toString();
      //printf("dump2 str is %s \n",str->toChars());
      if(!str->equals(tt)) {
        printf("---[TestMappedFile read case2] [FAILED]--- \n");
        break;
      }
      break;
    }
}
