#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "FileOutputStream.hpp"

int main() {
    //writeline
    File file = createFile("abc.txt");
    FileOutputStream stream = createFileOutputStream(file);
    stream->open(st(FileOutputStream)::FileOpenType::Trunc);
    stream->writeString("hello world ,i am c++ \n");
    stream->flush();
    stream->close();
}
