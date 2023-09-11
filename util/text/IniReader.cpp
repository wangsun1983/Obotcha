#include "IniReader.hpp"
#include "InitializeException.hpp"
#include "Log.hpp"

namespace obotcha {

sp<_IniReader> _IniReader::loadContent(String content) {
    mContent = content;
    return AutoClone(this);
}

sp<_IniReader> _IniReader::loadFile(File file) {
    if (file == nullptr || !file->exists()) {
        Trigger(InitializeException, "parse fail")
    }
    mFilePath = file->getAbsolutePath();
    return AutoClone(this);
}

IniValue _IniReader::get() {
    IniValue iniValue = createIniValue();
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