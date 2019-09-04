#include "FileOutputStream.hpp"

namespace obotcha {

_FileOutputStream::_FileOutputStream(File file) {
    mPath = createString(file->getAbsolutePath());    
}

_FileOutputStream::_FileOutputStream(String path) {
    mPath = createString(path);
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
    char *p = buff->toValue();
    //printf("write %s,size is %d \n",p,buff->size());
    fstream.write(buff->toValue(),buff->size());
    return buff->size();
}

long _FileOutputStream::write(ByteArray buff,long size) {
    char *p = buff->toValue();
    long length = buff->size() > size?size:buff->size();    
    fstream.write(buff->toValue(),length);
    return length;
}

bool _FileOutputStream::writeString(String s) {
    fstream<<s->toChars();
    return true;
}

bool _FileOutputStream::open() {
    return this->open(FileOpenType::Append);
}

bool _FileOutputStream::open(FileOpenType opentype) {
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