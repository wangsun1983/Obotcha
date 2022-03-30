#ifndef __OBOTCHA_INI_READER_H__
#define __OBOTCHA_INI_READER_H__

#include "iniparser.h"

#include "File.hpp"
#include "HashMap.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "IniValue.hpp"

namespace obotcha {

class _IniIterator;

DECLARE_CLASS(IniReader) {
public:
    friend class _IniIterator;

    _IniReader(String content);

    _IniReader(File file);

    ~_IniReader();

    IniValue parse();

private:

    String filepath;
};

} // namespace obotcha

#endif