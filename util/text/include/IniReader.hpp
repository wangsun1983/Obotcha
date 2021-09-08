#ifndef __OBOTCHA_INI_READER_H__
#define __OBOTCHA_INI_READER_H__

#include "iniparser.h"

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "File.hpp"
#include "IniValue.hpp"
#include "HashMap.hpp"

namespace obotcha {

class _IniIterator;

DECLARE_CLASS(IniReader) {

public:
    friend class _IniIterator;

    _IniReader(String content);

    _IniReader(File file);
    
    ~_IniReader();

    HashMap<String,String> get(String section = createString(""));
    HashMap<String,HashMap<String,String>> getAll();

private:
    static String RootSectionName;

    String filepath;

    dictionary * dict;

    void parse();
    
    //<Section,HashMap<Key,Value>
    HashMap<String,HashMap<String,String>> mIniValues;
};

}

#endif