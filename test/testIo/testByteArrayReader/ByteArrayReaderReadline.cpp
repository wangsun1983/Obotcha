#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Executors.hpp"
#include "Barrier.hpp"
#include "ByteArrayReader.hpp"
#include "File.hpp"
#include "FileInputStream.hpp"

using namespace obotcha;

int bytearray_read_line() {
    File f = createFile("test.txt");
    FileInputStream stream = createFileInputStream(f);
    stream->open();
    ByteArray arr = stream->readAll();
    ByteArrayReader reader = createByteArrayReader(arr);
    while(1) {
        String t = reader->readLine();
        if(t == nullptr) {
            return 1;
        }
        printf("t is %s,remain size is %d \n",t->toChars(),reader->getRemainSize());
    }
}