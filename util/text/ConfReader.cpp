#include "ConfReader.hpp"
#include "ConfValue.hpp"
#include "Error.hpp"
#include "InitializeException.hpp"

extern "C"{
    #include "ccl.h"
}

namespace obotcha {

_ConfReader::_ConfReader(const char* path) {
    mConfFile = createFile(path);
    if(!mConfFile->exists()) {
        throwInitializeException("File Not Exist");
    }

    parse();
}

_ConfReader::_ConfReader(String path) {
    mConfFile = createFile(path);
    if(!mConfFile->exists()) {
        throwInitializeException("File Not Exist");
    }

    parse();
}

_ConfReader::_ConfReader(File file) {
    mConfFile = file;
    if(!mConfFile->exists()) {
        throwInitializeException("File Not Exist");
    }

    parse();
}

int _ConfReader::setFile(const char* path) {
    mConfFile = createFile(path);
    if(!mConfFile->exists()) {
        return -FileNotExists;
    }

    return parse();
}
    
int _ConfReader::setFile(String path) {
    mConfFile = createFile(path);
    if(!mConfFile->exists()) {
        return -FileNotExists;
    }

    return parse();
}
    
int _ConfReader::setFile(File file) {
    mConfFile = file;
    if(!mConfFile->exists()) {
        return -FileNotExists;
    }

    return parse();
}

int _ConfReader::parse() {
    if(!mConfFile->exists()) {
        return -FileNotExists;
    }

    mConfValue = createConfValue();
    mConfValue->config.comment_char='#';
    mConfValue->config.sep_char='=';
    mConfValue->config.str_char='"';

    ccl_t * pair = &(mConfValue->config);
    if(0 == ccl_parse(pair,(const char *)mConfFile->getAbsolutePath()->toChars())) {
        return 0;
    }

    return -1;
}

ConfValue _ConfReader::get() {
    return mConfValue;
}

_ConfReader::~_ConfReader() {

}

String _ConfReader::get(String tag) {
    const char *value = ccl_get(&(mConfValue->config),(const char*)tag->toChars());
    if(value == nullptr || value[0] == 0) {
        return nullptr;
    }

    return createString(value);
}

}