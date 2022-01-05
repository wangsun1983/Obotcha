#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <sstream>

#include "ArrayList.hpp"
#include "InitializeException.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "File.hpp"
#include "LineReader.hpp"

namespace obotcha {

_LineReader::_LineReader(File file):mFileStream(file->getAbsolutePath()->toChars(),std::ifstream::in) {
    if (!file->exists()) {
        Trigger(InitializeException, "file not exists");
    }
    type = ReadFile;
}

_LineReader::_LineReader(String str) {
    type = ReadContent;
    mStringStream <<str->toChars();
}

_LineReader::_LineReader(ByteArray data) {
    type = ReadContent;
    mStringStream <<data->toValue();
}

String _LineReader::readLine() {    
    std::string s;

    switch(type) {
        case ReadContent:
        if (std::getline(mStringStream, s)) {
            return createString(s);
        }
        break;

        case ReadFile:
        if (std::getline(mFileStream, s)) {
            return createString(s);
        }
        break;
    }
    

    return nullptr;
}

void _LineReader::reset() {
    switch(type) {
        case ReadContent:
            mStringStream.clear();
            mStringStream.seekg(0, mStringStream.beg);
            break;
        
        case ReadFile:
            mFileStream.seekg(0);
        break;
    }
    
}

_LineReader::~_LineReader() {
    switch(type) {
        case ReadContent:
            //mStringStream.close();
        break;
        
        case ReadFile:
            mFileStream.close();
        break;
    }
    
}

} // namespace obotcha
