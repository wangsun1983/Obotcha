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
    //mHashMap = createHashMap<String,String>();
}


_ConfReader::_ConfReader(String path) {
    conf_file = createFile(path);
    //initConfig();
    //mHashMap = createHashMap<String,String>();
}


_ConfReader::_ConfReader(File file) {
    conf_file = file;
    //mHashMap = createHashMap<String,String>();
}

void _ConfReader::setFile(const char* path) {
    conf_file = createFile(path);
}
    
void _ConfReader::setFile(String path) {
    conf_file = createFile(path);
}
    
void _ConfReader::setFile(File file) {
    conf_file = file;
}

int _ConfReader::refresh() {
    return parse();
}

int _ConfReader::parse() {
    if(!conf_file->exists()) {
        return -ConfReaderFailNoFile;
    }

    mConfValue = createConfValue();
    mConfValue->config.comment_char='#';
    mConfValue->config.sep_char='=';
    mConfValue->config.str_char='"';

    ccl_t * pair = &(mConfValue->config);
    if(0 == ccl_parse(pair,(const char *)conf_file->getAbsolutePath()->toChars())) {
        //ConfIterator iterator = mConfValue->getIterator();
        //while(iterator->hasValue()) {
        //    mHashMap->put(iterator->getTag(),iterator->getValue());
        //    iterator->next();
        //}
        return 0;
    }

    return -ConfReaderFailParseErr;
}

ConfValue _ConfReader::get() {
    return mConfValue;
}

_ConfReader::~_ConfReader() {

}

String _ConfReader::get(String tag) {
    const char *value = ccl_get(&(mConfValue->config),(const char*)tag->toChars());
    return createString(value);
}


}