/**
 * @file FileInputStream.cpp
 * @brief A file output stream is an output stream for writing data to File
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include "FileOutputStream.hpp"

namespace obotcha {

_FileOutputStream::_FileOutputStream(File file) {
    mPath = file->getAbsolutePath();    
}

_FileOutputStream::_FileOutputStream(String path) {
    mPath = path;
}

_FileOutputStream::_FileOutputStream(const char *path) {
    mPath = createString(path);
}

bool _FileOutputStream::write(char c) {
    if(!fstream.is_open()) {
        return false;
    }
    
    fstream << c;
    return true;
}
    
long _FileOutputStream::write(ByteArray buff) {
    if(!fstream.is_open()) {
        return false;
    }
    
    fstream.write((char *)buff->toValue(),buff->size());
    return buff->size();
}

long _FileOutputStream::write(ByteArray buff,long size) {
    if(buff == nullptr || buff->size() < size) {
        return -1;
    }
 
    fstream.write((char *)buff->toValue(),size);
    return size;
}

bool _FileOutputStream::writeString(String s) {
    fstream<<s->toChars();
    return true;
}

bool _FileOutputStream::open() {
    if(fstream.is_open()) {
        return false;
    }

    return this->open(FileOpenType::Append);
}

bool _FileOutputStream::open(int opentype) {
    if(fstream.is_open()) {
        return false;
    }

    switch(opentype) {
        case FileOpenType::Append:
            fstream.open(mPath->toChars(),std::ios::app);
        break;

        case FileOpenType::Trunc:
            fstream.open(mPath->toChars(),std::ios::trunc);
        break;
    }

    return fstream.is_open();
}
    
void _FileOutputStream::close() {
    if(fstream.is_open()) {
        fstream.close();
    }
}

void _FileOutputStream::flush() {
    if(fstream.is_open()) {
        fstream.flush();
    }
}

_FileOutputStream::~_FileOutputStream() {
    this->close();
}

}