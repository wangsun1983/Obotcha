#include "FileOutputStream.hpp"

namespace obotcha {

_FileOutputStream::_FileOutputStream(File file) {
    mPath = createString(file->getAbsolutePath());    
}

_FileOutputStream::_FileOutputStream(String path) {
    mPath = createString(path);
}

bool _FileOutputStream::write(char c) {
    fstream << c;
    return true;
}
    
bool _FileOutputStream::write(ByteArray buff) {
    fstream.write(buff->toValue(),buff->size());
    return true;
}

bool _FileOutputStream::writeString(String s) {
    fstream<<s->toChars();
    return true;
}
   
bool _FileOutputStream::open(FileOpenType opentype) {
    switch(opentype) {
        case Append:
            fstream.open(mPath->toChars(),std::ios::app);
        break;

        case Trunc:
            fstream.open(mPath->toChars(),std::ios::trunc);
        break;
    }

    return fstream.is_open();
}
    
void _FileOutputStream::close() {
    fstream.close();
}

void _FileOutputStream::flush() {
    fstream.flush();
}

}