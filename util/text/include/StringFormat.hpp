#ifndef __STRING_FORMAT_HPP__
#define __STRING_FORMAT_HPP__

#include <stdarg.h>

#include "String.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(StringFormat)
{
public:
    _StringFormat();

    String format(char *fmt, ...);

private:
    String _format(String fmt,va_list args);
};

}

#endif