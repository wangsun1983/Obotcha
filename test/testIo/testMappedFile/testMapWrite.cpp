#include <stdio.h>

#include "File.hpp"
#include "FileInputStream.hpp"
#include "FileOutputStream.hpp"
#include "FileNotFoundException.hpp"
#include "System.hpp"
#include "MappedFile.hpp"

using namespace obotcha;

void testMapWrite() {
    //int fd = open("./tmp/abc.txt",O_CREAT | O_RDWR | O_TRUNC,S_IRUSR | S_IWUSR);
    //char *txt = "hello world,this is a mapped file test";
    //write(fd,txt,strlen(txt));
    //close(fd);

    while(1) {
      File f = createFile("./tmp/write_test.txt");
      f->createNewFile();
      
      MappedFile file = createMappedFileBuilder("./tmp/write_test.txt")->setSize(256)->create();
      ByteArray data = file->getData();
      char v[128] = "hello world,this is a write test";
      data->fillFrom((byte *)&v[0],0,128);

      break;
    }
}
