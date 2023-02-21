#include "ConfReader.hpp"
#include "Error.hpp"
#include "InitializeException.hpp"

extern "C" {
#include "ccl.h"
}

namespace obotcha {

_ConfReader::_ConfReader(String content) {
    this->mContent = content;
    parse();
}

_ConfReader::_ConfReader(File file) {
    mConfFile = file;
    if (!mConfFile->exists()) {
        Trigger(InitializeException, "File Not Exist");
    }

    parse();
}

int _ConfReader::parse() {
    if(mValue == nullptr) {
        mValue = createConfValue();
    }

    mValue->config.comment_char = '#';
    mValue->config.sep_char = '=';
    mValue->config.str_char = '"';

    
    if(mConfFile != nullptr) {
        if (0 == ccl_parse(&mValue->config,
                        (const char *)mConfFile->getAbsolutePath()->toChars())) {
            return 0;
        }
    } else if(mContent != nullptr) {
        if (0 == ccl_parse_content(&mValue->config,(char *)mContent->toChars())) {
            return 0;
        }
    }

    return -1;
}

_ConfReader::~_ConfReader() {
}

ConfValue _ConfReader::get() {
    return mValue;
}

} // namespace obotcha