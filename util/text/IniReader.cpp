#include "IniValue.hpp"
#include "IniReader.hpp"
#include "InitializeException.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



namespace obotcha {

_IniReader::_IniReader(String content) {
    //TODO
}

_IniReader::_IniReader(File file) {
    if(file == nullptr || !file->exists()) {
        Trigger(InitializeException,"parse fail \n");
    }

    filepath = file->getAbsolutePath();
    mIniValue = parse();
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

sp<_IniValue> _IniReader::parse(String content) {
    //TODO
    return nullptr;
}


}