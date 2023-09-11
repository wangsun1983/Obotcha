#include "ConfReader.hpp"
#include "InitializeException.hpp"
#include "Inspect.hpp"

extern "C" {
#include "ccl.h"
}

namespace obotcha {

sp<_ConfReader> _ConfReader::loadContent(String content) {
    mContent = content;
    parse();
    return AutoClone(this);
}

sp<_ConfReader> _ConfReader::loadFile(File file) {
    mConfFile = file;
    Panic(!mConfFile->exists(),InitializeException, "File Not Exist")
    parse();
    return AutoClone(this);
}

int _ConfReader::parse() {
    mValue = createConfValue();
    mValue->mConfig.comment_char = '#';
    mValue->mConfig.sep_char = '=';
    mValue->mConfig.str_char = '"';
    
    //if fail to parse file,try to parse content.
    if (mConfFile != nullptr) {
        return ccl_parse(&mValue->mConfig,mConfFile->getAbsolutePath()->toChars());
    } else if(mContent != nullptr) {
        return ccl_parse_content(&mValue->mConfig,mContent->toChars());
    }
    
    Trigger(InitializeException,"no conf file or content!")
}

ConfValue _ConfReader::get() const {
    return mValue;
}

} // namespace obotcha