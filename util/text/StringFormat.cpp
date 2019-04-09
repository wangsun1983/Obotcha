#include <vector>

#include "String.hpp"
#include "StringFormat.hpp"

namespace obotcha {

#define DEFAULT_STRING_BUFF 512

_StringFormat::_StringFormat() {
    //TODO
}

String _StringFormat::format(String fmt, ...) {
    va_list args;
    va_start(args, fmt->toChars());
    String str = _format(fmt->toChars(), args);
    va_end(args);

    return str;
}

String _StringFormat::_format(String fmt,va_list args) {
    constexpr size_t oldlen = DEFAULT_STRING_BUFF;
    char buffer[oldlen];
    va_list argscopy;
    va_copy(argscopy, args);
    size_t newlen = vsnprintf(&buffer[0], oldlen, fmt->toChars(), args) + 1;
    newlen++;  
    if (newlen > oldlen) {
        std::vector<char> newbuffer(newlen);
        vsnprintf(newbuffer.data(), newlen, fmt->toChars(), argscopy);
        return createString(newbuffer.data());
    }
    return createString(buffer);
}

}