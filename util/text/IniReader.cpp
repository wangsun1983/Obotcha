#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "HashMap.hpp"
#include "IniReader.hpp"
#include "InitializeException.hpp"
#include "Log.hpp"

namespace obotcha {

_IniReader::_IniReader(String content) {
    mContent = content;
}

_IniReader::_IniReader(File file) {
    if (file == nullptr || !file->exists()) {
        Trigger(InitializeException, "parse fail")
    }

    mFilePath = file->getAbsolutePath();
}

IniValue _IniReader::parse() {
    IniValue iniValue = createIniValue();
    if (mFilePath!= nullptr && !st(File)::exists(mFilePath)) {
        LOG(ERROR) << "InitReader file not exsits";
        return nullptr;
    }

    if(iniValue->dict != nullptr) {
        iniparser_freedict(iniValue->dict);
    }
    
    if(mFilePath != nullptr) {
        iniValue->dict = iniparser_load(mFilePath->toChars());
    } else {
        iniValue->dict = iniparser_load_content(mContent->toChars());
    }

    iniValue->init();
    return iniValue;
}

} // namespace obotcha