#ifndef __OBOTCHA_INI_READER_H__
#define __OBOTCHA_INI_READER_H__

#include "File.hpp"
#include "Object.hpp"
#include "IniValue.hpp"

namespace obotcha {

DECLARE_CLASS(IniReader) {
public:
    explicit _IniReader() = default;
    sp<_IniReader> loadContent(String);
    sp<_IniReader> loadFile(File);
    IniValue get();
private:
    String mFilePath = nullptr;
    String mContent = nullptr;
};

} // namespace obotcha

#endif