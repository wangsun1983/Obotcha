#include <fcntl.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "FileNodeWriter.hpp"
#include "FileNotFoundException.hpp"

namespace obotcha {

_FileNodeWriter::_FileNodeWriter(String path) {
    mPath = path;
    mFd = open(path->toChars(),O_WRONLY);
    if(mFd < 0) {
        throw FileNotFoundException("File not exist");
    }
}

int _FileNodeWriter::write(int v) {
    String value = createString(v);
    return ::write(mFd,value->toChars(),value->size());
}

int _FileNodeWriter::write(long v) {
    String value = createString(v);
    return ::write(mFd,value->toChars(),value->size());
}

int _FileNodeWriter::write(String v) {
    return ::write(mFd,v->toChars(),v->size());
}

int _FileNodeWriter::write(ByteArray value) {
    return ::write(mFd,value->toValue(),value->size());
}

String _FileNodeWriter::getPath() {
    return mPath;
}

_FileNodeWriter::~_FileNodeWriter() {
    if(mFd >= 0) {
        close(mFd);
        mFd = -1;
    }
}

}

