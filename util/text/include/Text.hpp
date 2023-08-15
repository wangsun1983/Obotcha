#ifndef __OBOTCHA_TEXT_H__
#define __OBOTCHA_TEXT_H__

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(Text) {
public:
    enum class Format {
        Json = 0,
        Xml 
    };

    enum class Syntax {
        Name = 0,
        Value
    };
};

} // namespace obotcha
#endif