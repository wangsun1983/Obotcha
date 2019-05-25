#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>
#include <sys/types.h>  
#include <sys/stat.h>
#include <fcntl.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "FileNodeReader.hpp"
#include "FileInputStream.hpp"

namespace obotcha {

int _FileNodeReader::readInt(String path) {
    char buff[256];
    memset(buff,0,256);

    int fd = open(path->toChars(),O_RDONLY);
    read(fd,buff,256);
    close(fd);

    return createString(buff)->toBasicInt();
}

long _FileNodeReader::readLong(String path) {
    char buff[512];
    memset(buff,0,512);

    int fd = open(path->toChars(),O_RDONLY);
    read(fd,buff,512);
    close(fd);

    return createString(buff)->toBasicLong();
}

String _FileNodeReader::readString(String path) {
    char buff[1024*16];
    memset(buff,0,1024*16);
    
    int fd = open(path->toChars(),O_RDONLY);
    read(fd,buff,1024*16);
    close(fd);

    return createString(buff);
}

String _FileNodeReader::readString(String path,int buffsize) {
    char buff[buffsize];

    int fd = open(path->toChars(),O_RDONLY);
    read(fd,buff,buffsize);
    close(fd);

    return createString(&buff[0]);
}


}

