#include "IniValue.hpp"
#include "IniReader.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



namespace obotcha {

_IniReader::_IniReader(const char * path) {
    filepath = createString(path);
}

_IniReader::_IniReader(String path) {
    filepath = path;
}

_IniReader::_IniReader(File file) {
    filepath = file->getAbsolutePath();
}

IniValue _IniReader::parse() {
    dictionary *dict = iniparser_load(filepath->toChars());
    
    if(dict == nullptr) {
        return nullptr;
    }

    return createIniValue(dict);
}


}