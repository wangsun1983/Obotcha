#ifndef __OBOTCHA_CONF_READER_H__
#define __OBOTCHA_CONF_READER_H__

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

    int setFile(const char* path);
    
    int setFile(String path);
    
    int setFile(File file);

    sp<_ConfValue> get();

    String get(String);

    int refresh();

    ~_ConfReader();

private:
    int parse();

    File mConfFile;
    
    sp<_ConfValue> mConfValue;
};

}

#endif