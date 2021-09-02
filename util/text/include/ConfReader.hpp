#ifndef __OBOTCHA_CONF_READER_H__
#define __OBOTCHA_CONF_READER_H__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "IniValue.hpp"
#include "File.hpp"

extern "C" {
#include "ccl.h"
}

namespace obotcha {

class _ConfIterator;

DECLARE_CLASS(ConfReader) {

public:
    friend class _ConfIterator;

    _ConfReader(const char* path);

    _ConfReader(String path);

    _ConfReader(File file);

    String get(String);

    sp<_ConfIterator> getIterator();

    ~_ConfReader();

private:
    int parse();

    File mConfFile;

    struct ccl_t config;
};

DECLARE_CLASS(ConfIterator) {
public:
    _ConfIterator(ConfReader r);

    String getTag();
    
    String getValue();

    bool hasValue();
    
    bool next();

private:
    sp<_ConfReader> reader;
    struct ccl_pair_t* iterator;
};


}

#endif