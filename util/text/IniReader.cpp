#include "IniValue.hpp"
#include "IniReader.hpp"
#include "InitializeException.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



namespace obotcha {

_IniReader::_IniReader(const char * path) {
    filepath = createString(path);
    mIniValue = parse();
    if(mIniValue == nullptr) {
        throw InitializeException("parse fail \n");
    }
}

_IniReader::_IniReader(String path) {
    filepath = path;
    mIniValue = parse();
    if(mIniValue == nullptr) {
        throw InitializeException("parse fail \n");
    }
}

_IniReader::_IniReader(File file) {
    filepath = file->getAbsolutePath();
    mIniValue = parse();
    if(mIniValue == nullptr) {
        throw InitializeException("parse fail \n");
    }
}

sp<_IniValue> _IniReader::get() {
    return mIniValue;
}

IniValue _IniReader::parse() {
    if(!st(File)::exists(filepath)) {
        return nullptr;
    }
    
    dictionary *dict = iniparser_load(filepath->toChars());
    
    if(dict == nullptr) {
        return nullptr;
    }

    return createIniValue(dict);
}


}