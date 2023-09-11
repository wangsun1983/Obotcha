#ifndef __OBOTCHA_INI_WRITER_H__
#define __OBOTCHA_INI_WRITER_H__

#include "iniparser.h"

#include "File.hpp"
#include "Object.hpp"
#include "IniValue.hpp"

namespace obotcha {

DECLARE_CLASS(IniWriter) {
public:
    explicit _IniWriter(File);
    explicit _IniWriter(String);
    
    int write(IniValue) const;
private:
    File mFile;
};

} // namespace obotcha

#endif