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
    explicit _ConfReader() = default;
    sp<_ConfReader> loadContent(String);
    sp<_ConfReader> loadFile(File);
    ConfValue get() const;
    ~_ConfReader() override = default;

private:
    int parse();
    File mConfFile = nullptr;
    ConfValue mValue = nullptr;
    String mContent;
};

} // namespace obotcha

#endif