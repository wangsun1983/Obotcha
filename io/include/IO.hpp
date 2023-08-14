#ifndef __OBOTCHA_IO_HPP__
#define __OBOTCHA_IO_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "FileDescriptor.hpp"

namespace obotcha {

DECLARE_CLASS(IO) {
public:
    enum class Endianness {
        Little = 0,
        Big
    };
};

}
#endif
