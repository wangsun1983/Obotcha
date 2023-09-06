#ifndef __OBOTCHA_VALUE_NOT_FOUND_EXCEPTION_HPP__
#define __OBOTCHA_VALUE_NOT_FOUND_EXCEPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fstream>
#include <string>

#include "Object.hpp"

#include "String.hpp"
#include "Exception.hpp"

namespace obotcha {

DECLARE_EXCEPTION(ValueNotFoundException) {
public:
	ValueNotFoundException() = default;
};

#if ENABLE_NOT_FOUND_VALUE
template<typename T>
class __NotFoundValue {
public:
    T getValue() {
        return nullptr;
    }
};


#define MACRO_VALUE_NOT_FOUND(X) \
template<>\
class __NotFoundValue<X> { \
public:\
    X getValue() {\
        Trigger(ValueNotFoundException,"not found")\
    }\
};\

MACRO_VALUE_NOT_FOUND(int)
MACRO_VALUE_NOT_FOUND(bool)
MACRO_VALUE_NOT_FOUND(double)
MACRO_VALUE_NOT_FOUND(float)
MACRO_VALUE_NOT_FOUND(long)
MACRO_VALUE_NOT_FOUND(uint8_t)
MACRO_VALUE_NOT_FOUND(uint16_t)
MACRO_VALUE_NOT_FOUND(uint32_t)
MACRO_VALUE_NOT_FOUND(uint64_t)
MACRO_VALUE_NOT_FOUND(std::string)
#endif

}
#endif
