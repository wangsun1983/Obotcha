#ifndef __CONF_READER_H__
#define __CONF_READER_H__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "IniValue.hpp"
#include "File.hpp"
#include "rapidxml.hpp"
#include "XmlValue.hpp"
#include "HashMap.hpp"

extern "C" {
#include "ccl.h"
}

namespace obotcha {

class _ConfValue;

DECLARE_SIMPLE_CLASS(ConfReader) {

public:
    _ConfReader(const char* path);

    _ConfReader(String path);

    _ConfReader(File file);

    void setFile(const char* path);
    
    void setFile(String path);
    
    void setFile(File file);

    int parse();

    //HashMap<String,String>getAll();

    sp<_ConfValue> get();

    String get(String);

    int refresh();

    ~_ConfReader();

private:
    File conf_file;
    
    void initConfig();

    //HashMap<String,String> mHashMap;

    sp<_ConfValue> mConfValue;
};

}

#endif