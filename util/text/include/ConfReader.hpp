#ifndef __CONF_READER_H__
#define __CONF_READER_H__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "IniValue.hpp"
#include "File.hpp"
#include "rapidxml.hpp"
#include "XmlValue.hpp"

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

    sp<_ConfValue> parse();

    ~_ConfReader();

private:
    File conf_file;
    
    void initConfig();
};

}

#endif