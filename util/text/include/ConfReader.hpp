#ifndef __OBOTCHA_CONF_READER_H__
#define __OBOTCHA_CONF_READER_H__

#include "File.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ConfValue.hpp"

extern "C" {
#include "ccl.h"
}

namespace obotcha {

DECLARE_CLASS(ConfReader) {
public:
    friend class _ConfIterator;

    _ConfReader(String content);

    _ConfReader(File file);

    ConfValue get();

    ~_ConfReader();

private:
    int parse();

    File mConfFile;

    //struct ccl_t config;
    ConfValue mValue;
    String mContent;
};

} // namespace obotcha

#endif