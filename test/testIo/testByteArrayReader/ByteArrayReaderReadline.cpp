#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Barrier.hpp"
#include "ByteArrayReader.hpp"
#include "File.hpp"
#include "FileInputStream.hpp"
#include "FileOutputStream.hpp"

using namespace obotcha;

void testReadline() {

    //prepare data
    File file = createFile("./tmp/base_data");
    file->removeAll();
    if(!file->exists()) {
      file->createNewFile();
      FileOutputStream stream = createFileOutputStream(file);
      stream->open(st(OutputStream)::Trunc);
      stream->write(createString("hello\nworld\nni\nhao")->toByteArray());
      stream->close();
    }


    FileInputStream stream = createFileInputStream(file);
    stream->open();
    ByteArray arr = stream->readAll();
    ByteArrayReader reader = createByteArrayReader(arr);
    ArrayList<String> contents = createArrayList<String>();
    contents->add(createString("hello"));
    contents->add(createString("world"));
    contents->add(createString("ni"));
    contents->add(createString("hao"));

    for(int i = 0;i<4;i++) {
        String t = reader->readLine();
        //printf("t is %s \n",t->toChars());
        if(!t->equals(contents->get(i))) {
          printf("---[TestByteArrayReader ReadLine case1] [FAILED]--- \n");
        }
    }
    //printf("------------- \n");
    String t2 = reader->readLine();
    if(t2 != nullptr) {
      printf("---[TestByteArrayReader ReadLine case2] [FAILED]--- \n");
    }

    printf("---[TestByteArrayReader ReadLine case100] [OK]--- \n");
}
