#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "UUID.hpp"
#include "Log.hpp"
#include "ZipFileStream.hpp"
#include "Exception.hpp"
#include "MethodNotSupportException.hpp"
#include "Md.hpp"

using namespace obotcha;

void testZipCompress() {
  while(1) {
    ZipFileStream stream = createZipFileStream();

    stream->compress("./tmp/base_data","./tmp/base_data_genzip.zip");
    File f = createFile("./tmp/base_data_genzip.zip");

    if(!f->exists()) {
      printf("---[LibraryFile Compress Test case1] [FAILED]--- \n");
      break;
    }

    //start decompress
    File f2 = createFile("./tmp/deCompress_check1/");
    f2->createDir();
    system("unzip ./tmp/base_data_genzip.zip -d ./tmp/deCompress_check1/");

    Md md = createMd(st(Md)::Md5);
    String base1 = md->encrypt(createFile("./tmp/base_data"));
    String decompress1 = md->encrypt(createFile("./tmp/deCompress_check1/base_data"));

    if(!base1->equals(decompress1)) {
      printf("---[LibraryFile Compress Test case2] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    ZipFileStream stream = createZipFileStream();

    stream->compressWithPassword("./tmp/base_data","./tmp/base_data_pwd_genzip.zip","123456");
    File f = createFile("./tmp/base_data_pwd_genzip.zip");

    if(!f->exists()) {
      printf("---[LibraryFile Compress Test case3] [FAILED]--- \n");
      break;
    }

    //start decompress
    File f2 = createFile("./tmp/deCompress_check2/");
    f2->createDir();
    system("unzip -P 123456 ./tmp/base_data_pwd_genzip.zip -d ./tmp/deCompress_check2/");

    Md md = createMd(st(Md)::Md5);
    String base1 = md->encrypt(createFile("./tmp/base_data"));
    String decompress1 = md->encrypt(createFile("./tmp/deCompress_check2/base_data"));

    if(!base1->equals(decompress1)) {
      printf("---[LibraryFile Compress Test case4] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[LibraryFile Compress Test case100] [OK]--- \n");
}
