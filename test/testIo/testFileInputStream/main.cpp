#include <stdio.h>

#include "File.hpp"
#include "FileInputStream.hpp"
#include "FileOutputStream.hpp"
#include "FileNotFoundException.hpp"
#include "System.hpp"

using namespace obotcha;

extern void testFileInputStreamReadAll();
extern void testFileInputStreamRead();
extern void testFileInputStreamReadTo();
extern void testFileInputStreamSeekTo();
extern void testFileInputStreamClose();
extern void testFileInputStreamReadNode();

int main() {
  //prepare data
  File file = createFile("./tmp/data.txt");
  printf("start main test \n");
  if(!file->exists()) {
    file->createNewFile();
      for(int i = 0;i<1024;i++) {
      FileOutputStream stream = createFileOutputStream(file);
      stream->open(st(OutputStream)::Append);
      String data = createString("");
      for(int i = 0;i < 1024;i++) {
        data = data->append(createString(st(System)::currentTimeMillis()));
      }
      stream->write(data->toByteArray());
      stream->close();
    }
  }
  printf("start main trace1 \n");
  testFileInputStreamReadNode();
  testFileInputStreamClose();
  testFileInputStreamReadAll();
  testFileInputStreamRead();
  testFileInputStreamReadTo();
  testFileInputStreamSeekTo();
}
