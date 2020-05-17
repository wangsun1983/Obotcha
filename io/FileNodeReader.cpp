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

_FileNodeReader::_FileNodeReader(String path,int buffsize) {
    mBuffer = (byte*)malloc(buffsize);

    mSize = buffsize;

    mPath = path;

    mFd = open(mPath->toChars(),O_RDONLY);
}

int _FileNodeReader::readInt() {
    memset(mBuffer,0,mSize);
    read(mFd,mBuffer,mSize);
    return createString(mBuffer)->toBasicInt();
}

long _FileNodeReader::readLong() {
    memset(mBuffer,0,mSize);
    read(mFd,mBuffer,mSize);
    return createString(mBuffer)->toBasicLong();
}

bool _FileNodeReader::readBoolean() {
    memset(mBuffer,0,mSize);
    read(mFd,mBuffer,mSize);
    return createString(mBuffer)->toBasicLong();
}

String _FileNodeReader::readString() {
    memset(mBuffer,0,mSize);
    read(mFd,mBuffer,mSize);;

    return createString(mBuffer);
}

String _FileNodeReader::getPath() {
    return mPath;
}

_FileNodeReader::~_FileNodeReader() {
    if(mBuffer != nullptr) {
        free(mBuffer);
        mBuffer = nullptr;
    }

    if(mFd >= 0) {
        close(mFd);
        mFd = -1;
    }
}


}

