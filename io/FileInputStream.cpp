#include "FileInputStream.hpp"

_FileInputStream::_FileInputStream(File f) {
    mPath = createString(f->getAbsolutePath());
}
    
_FileInputStream::_FileInputStream(String path) {
    mPath = createString(path);
}
    
int _FileInputStream::read() {
    //TODO
}

int _FileInputStream::read(char *buffer,int size) {
    fstream.read(buffer,size);
    return fstream.gcount();
}

bool _FileInputStream::open() {
    fstream.open(mPath->toChars());
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