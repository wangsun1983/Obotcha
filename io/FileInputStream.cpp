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
}

int _FileInputStream::read(ByteArray buff) {
    fstream.read(buff->toValue(),buff->size());
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

}