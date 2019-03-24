#include "ConfReader.hpp"
#include "ConfValue.hpp"

extern "C"{
    #include "ccl.h"
}

namespace obotcha {

void _ConfReader::initConfig() {

}

_ConfReader::_ConfReader(const char* path) {
    conf_file = createFile(path);
    //initConfig();
}


_ConfReader::_ConfReader(String path) {
    conf_file = createFile(path);
    //initConfig();
}


_ConfReader::_ConfReader(File file) {
    conf_file = file;
    initConfig();
}

sp<_ConfValue> _ConfReader::parse() {

    ConfValue value = createConfValue();
    value->config.comment_char='#';
    value->config.sep_char='=';
    value->config.str_char='"';

    ccl_t * pair = &(value->config);
    if(0 == ccl_parse(pair,conf_file->getAbsolutePath()->toChars())) {
        return value;
    }

    return nullptr;
}

_ConfReader::~_ConfReader() {

}

/*
String _ConfReader::get(String tag) {
    char *value = ccl_get(&config,tag->toChars());

    return createString(value)
}
*/


}