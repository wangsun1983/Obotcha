#ifndef __OBOTCHA_CONF_READER_H__
#define __OBOTCHA_CONF_READER_H__

#include "Object.hpp"
#include "File.hpp"
#include "ConfValue.hpp"

extern "C" {
#include "ccl.h"
}

namespace obotcha {

DECLARE_CLASS(ConfReader) {
public:
    friend class _ConfIterator;

    explicit _ConfReader(String content);

    explicit _ConfReader(File file);

    ConfValue get();

    ~_ConfReader() = default;

private:
    int parse();

    File mConfFile;
    ConfValue mValue;
    String mContent;
};

} // namespace obotcha

#endif