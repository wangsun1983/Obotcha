#include "ConfReader.hpp"
#include "Error.hpp"
#include "InitializeException.hpp"

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
    if (!mConfFile->exists()) {
        Trigger(InitializeException, "File Not Exist");
    }

    parse();
}

int _ConfReader::parse() {
    mValue = createConfValue();
    mValue->mConfig.comment_char = '#';
    mValue->mConfig.sep_char = '=';
    mValue->mConfig.str_char = '"';

    //if fail to parse file,try to parse content.
    if(parseFile() != 0) {
        return parseContent();
    }

    return 0;
}

//according ccl_parse
//0 if successful, nonzero otherwise
int _ConfReader::parseContent() {
    if(mConfFile != nullptr) {
        return ccl_parse(&mValue->mConfig,
                        (const char *)mConfFile->getAbsolutePath()->toChars());
    }
    return -1;
}

int _ConfReader::parseFile() {
    if(mContent != nullptr) {
        return ccl_parse_content(&mValue->mConfig,(char *)mContent->toChars());
    }
    return -1;
}

_ConfReader::~_ConfReader() {
}

ConfValue _ConfReader::get() {
    return mValue;
}

} // namespace obotcha