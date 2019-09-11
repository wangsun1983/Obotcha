#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "StringReader.hpp"
#include "ArrayList.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_StringReader::_StringReader(String v):mStringStream(v->getStdString()){
    if(v == nullptr) {
        throw createInitializeException(createString("StringReader error"));
    }
}
    
String _StringReader::readLine() {
    std::string s;
    if(std::getline(mStringStream,s)) {
        return createString(s.data());
    }

    return nullptr;
}

void _StringReader::reset() {
    mStringStream.clear();
    mStringStream.seekg(0,mStringStream.beg);
}

_StringReader::~_StringReader() {
    
}


}

