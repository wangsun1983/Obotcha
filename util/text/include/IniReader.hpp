#ifndef __OBOTCHA_INI_READER_H__
#define __OBOTCHA_INI_READER_H__

#include "iniparser.h"

#include "File.hpp"
#include "HashMap.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "IniValue.hpp"

namespace obotcha {

DECLARE_CLASS(IniReader) {
public:
    explicit _IniReader(String content);
    explicit _IniReader(File file);

    IniValue parse();

private:
    String mFilePath;
    String mContent;
};

} // namespace obotcha

#endif