#ifndef __INI_READER_H__
#define __INI_READER_H__

#include "iniparser.h"

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "IniValue.hpp"
#include "File.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(IniReader) {

public:
    _IniReader(const char* path);

    _IniReader(String path);

    _IniReader(File file);

    IniValue parse();

private:
    String filepath;    

};

}

#endif