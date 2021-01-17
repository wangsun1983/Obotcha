/**
 * @file FileInputStream.cpp
 * @brief FileInputStream obtains input bytes from a file in a file system.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */
#include <iostream>
#include "FileInputStream.hpp"
#include "FileNotFoundException.hpp"
#include "Log.hpp"

namespace obotcha {

_FileInputStream::_FileInputStream(File f) {
    mPath = f->getAbsolutePath();
}
    
_FileInputStream::_FileInputStream(String path) {
    mPath = createString(path);
}

long _FileInputStream::read(ByteArray buff) {
    if(!fstream.is_open()) {
        return -1;
    }

    fstream.read((char *)buff->toValue(),buff->size());
    return fstream.gcount();
}

long _FileInputStream::readByLength(ByteArray buffer,int pos,int len) {
    if(!fstream.is_open()) {
        return -1;
    }

    fstream.read((char *)buffer->toValue() + pos,len);
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
    if(fstream.is_open()) {
        return false;
    }

    fstream.open(mPath->toChars(),std::ios::in|std::ios::binary);
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