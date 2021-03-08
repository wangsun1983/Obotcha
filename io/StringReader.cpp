#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "StringReader.hpp"
#include "ArrayList.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_StringReader::_StringReader(FileInputStream stream){
    if(stream == nullptr) {
        Trigger(InitializeException,"StringReader error");
    }

    ByteArray content = stream->readAll();
    mStringStream << content->toString()->getStdString();
}
    
String _StringReader::readLine() {
    std::string s;
    if(std::getline(mStringStream,s)) {
        return createString(s);
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

