#include <iostream>
#include "FileInputStream.hpp"
#include "Exception.hpp"
#include "FileNotFoundException.hpp"

namespace obotcha {

_FileInputStream::_FileInputStream(File f) {
    mPath = createString(f->getAbsolutePath());
}
    
_FileInputStream::_FileInputStream(String path) {
    mPath = createString(path);
}
    
int _FileInputStream::read() {
    if(!fstream.is_open()) {
        throw createFileNotFoundException(createString("inputstream path:")->append(mPath));
    }

    int value = 0;
    fstream.read((char *)&value,sizeof(int));
    return value;
}

long _FileInputStream::read(ByteArray buff) {
    if(!fstream.is_open()) {
        return -1;
    }

    fstream.read((char *)buff->toValue(),buff->size());
    return fstream.gcount();
}

long _FileInputStream::read(long index,ByteArray buffer) {
    if(!fstream.is_open()) {
        return -1;
    }

    fstream.seekg(index);
    fstream.read((char *)buffer->toValue(),buffer->size());
    return fstream.gcount();
}

ByteArray _FileInputStream::readAll() {
    if(!fstream.is_open()) {
        return nullptr;
    }

    fstream.seekg (0, fstream.end);
    long srcSize = fstream.tellg();
    fstream.seekg (0, fstream.beg);

    ByteArray content = createByteArray(srcSize);
    fstream.read((char *)content->toValue(),srcSize);
    return content;
}

bool _FileInputStream::open() {
    fstream.open(mPath->toChars(),ios::in|ios::binary);
    return fstream.is_open();
}

void _FileInputStream::close() {
    if(fstream.is_open()) {
        fstream.close();
    }
}

void _FileInputStream::reset() {
    if(fstream.is_open()) {
        fstream.clear();
        fstream.seekg(0,fstream.beg);
    }
}

String _FileInputStream::readLine() {
    if(!fstream.is_open()) {
        return nullptr;
    }

    std::string s;
    if(std::getline(fstream,s)) {
        return createString(s.data());
    }

    return nullptr;
}

_FileInputStream::~_FileInputStream() {
    close();
}

}