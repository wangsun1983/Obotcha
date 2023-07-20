#include "ConfReader.hpp"
#include "InitializeException.hpp"
#include "Inspect.hpp"

extern "C" {
#include "ccl.h"
}

namespace obotcha {

_ConfReader::_ConfReader(String content) {
    mContent = content;
    parse();
}

_ConfReader::_ConfReader(File file) {
    mConfFile = file;
    Panic(!mConfFile->exists(),InitializeException, "File Not Exist");
    parse();
}

int _ConfReader::parse() {
    mValue = createConfValue();
    mValue->mConfig.comment_char = '#';
    mValue->mConfig.sep_char = '=';
    mValue->mConfig.str_char = '"';
    
    //if fail to parse file,try to parse content.
    if (mConfFile != nullptr) {
        return ccl_parse(&mValue->mConfig,
            (const char *)mConfFile->getAbsolutePath()->toChars());
    } else if(mContent != nullptr) {
        return ccl_parse_content(&mValue->mConfig,(char *)mContent->toChars());
    }    
    
    Trigger(InitializeException,"no conf file or content!");
}

ConfValue _ConfReader::get() {
    return mValue;
}

} // namespace obotcha