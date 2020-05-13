#ifndef __OBOTCHA_INI_READER_H__
#define __OBOTCHA_INI_READER_H__

#include "iniparser.h"

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "File.hpp"
#include "IniValue.hpp"

namespace obotcha {

class _IniValue;

DECLARE_SIMPLE_CLASS(IniReader) {

public:
    _IniReader(String content);

    _IniReader(File file);

    sp<_IniValue> get();

private:
    String filepath;

    sp<_IniValue> mIniValue; 

    sp<_IniValue> parse();

    sp<_IniValue> parse(String);
    
};

}

#endif