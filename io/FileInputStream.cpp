#include <iostream>
#include "FileInputStream.hpp"

namespace obotcha {

_FileInputStream::_FileInputStream(File f) {
    mPath = createString(f->getAbsolutePath());
}
    
_FileInputStream::_FileInputStream(String path) {
    mPath = createString(path);
}
    
int _FileInputStream::read() {
    //TODO
    return 0;
}

int _FileInputStream::read(ByteArray buff) {
    fstream.read(buff->toValue(),buff->size());
    return fstream.gcount();
}

void _FileInputStream::readAll(ByteArray content) {
    ifstream fsRead;
    fsRead.open(mPath->getStdString(), ios::in|ios::binary);
    //cout<<"mPath->getStdString is "<<mPath->getStdString()<<endl;
    if (!fsRead) {
        return;
    }

    fsRead.seekg(0, fsRead.end);
    long srcSize = fsRead.tellg();
    //printf("readAll size is %ld \n",srcSize);

    long buffSize = content->size();

    long currentSize = buffSize>srcSize?srcSize:buffSize;
    fstream.read(content->toValue(),currentSize);
}

ByteArray _FileInputStream::readAll() {
    //ifstream fsRead;
    //fsRead.open(mPath->getStdString(), ios::in|ios::binary);
    //cout<<"mPath->getStdString is "<<mPath->getStdString()<<endl;
    //if (!fsRead) {
    //    return nullptr;
    //}

    //fsRead.seekg(0, fsRead.end);
    //long srcSize = fsRead.tellg();
    //printf("readAll size is %ld \n",srcSize);
    //fsRead.close();
    fstream.seekg (0, fstream.end);
    long srcSize = fstream.tellg();
    fstream.seekg (0, fstream.beg);

    ByteArray content = createByteArray(srcSize);
    fstream.read(content->toValue(),srcSize);
    //char *p = content->toValue();
    //printf("read p[0] is %x \n",p[0]);
    //printf("read p[1] is %x \n",p[1]);
    //printf("readAll readsize is %d \n",fstream.gcount());
    return content;
}

bool _FileInputStream::open() {
    fstream.open(mPath->toChars(),ios::in|ios::binary);
    return fstream.is_open();
}

void _FileInputStream::close() {
    fstream.close();
}

String _FileInputStream::readLine() {
    std::string s;
    if(std::getline(fstream,s)) {
        return createString(s.data());
    }

    return nullptr;
}

}