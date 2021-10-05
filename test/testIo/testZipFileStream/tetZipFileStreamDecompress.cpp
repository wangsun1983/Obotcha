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

void testZipDecompress() {
  while(1) {
    ZipFileStream stream = createZipFileStream();
    File baseZipFile = createFile("./tmp/base_zip.zip");
    if(!baseZipFile->exists()) {
      printf("---[LibraryFile Decompress Test case1] [FAILED]--- \n");
      break;
    }

    File dir = createFile("./tmp/decompress_data/");
    dir->createDir();

    stream->deCompress("./tmp/base_zip.zip","./tmp/decompress_data/");
    File f = createFile("./tmp/decompress_data");
    if(!f->exists()) {
      printf("---[LibraryFile Decompress Test case2] [FAILED]--- \n");
      break;
    }

    Md md = createMd(st(Md)::Md5);
    String base1 = md->encrypt(createFile("./tmp/base_data"));
    String decompress1 = md->encrypt(createFile("./tmp/decompress_data/tmp/base_data"));

    if(!base1->equals(decompress1)) {
      printf("---[LibraryFile Decompress Test case3] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    ZipFileStream stream = createZipFileStream();
    File baseZipFile = createFile("./tmp/base_password_data.zip");
    if(!baseZipFile->exists()) {
      printf("---[LibraryFile Decompress Test case4] [FAILED]--- \n");
      break;
    }

    File dir = createFile("./tmp/decompress_data/");
    dir->createDir();

    stream->deCompressWithPassword("./tmp/base_password_data.zip","./tmp/decompress_password_data/","123456");
    File f = createFile("./tmp/decompress_password_data");
    if(!f->exists()) {
      printf("---[LibraryFile Decompress Test case5] [FAILED]--- \n");
      break;
    }

    Md md = createMd(st(Md)::Md5);
    String base1 = md->encrypt(createFile("./tmp/base_data"));
    String decompress1 = md->encrypt(createFile("./tmp/decompress_password_data/tmp/base_data"));

    if(!base1->equals(decompress1)) {
      printf("---[LibraryFile Decompress Test case6] [FAILED]--- \n");
      break;
    }
    break;
  }

  while(1) {
    Md md = createMd(st(Md)::Md5);
    String base1 = md->encrypt(createFile("./tmp/base_data"));

    ZipFileStream stream = createZipFileStream();
    File baseZipFile = createFile("./tmp/base_zip.zip");
    if(!baseZipFile->exists()) {
      printf("---[LibraryFile Decompress Test case7] [FAILED]--- \n");
      break;
    }

    stream->deCompress("./tmp/base_zip.zip");
    String decompress1 = md->encrypt(createFile("./tmp/base_data"));

    if(!base1->equals(decompress1)) {
      printf("---[LibraryFile Decompress Test case8] [FAILED]--- \n");
      break;
    }
    break;
  }

  printf("---[LibraryFile Decompress Test case100] [OK]--- \n");
}
