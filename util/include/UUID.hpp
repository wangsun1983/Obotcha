#ifndef __OBOTCHA_UUID_HPP__
#define __OBOTCHA_UUID_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "uuid.h"


namespace obotcha {

DECLARE_SIMPLE_CLASS(UUID) {

public:
    enum Type {
        Random = 0,
        Time,
        TimeSafe,
        Default,
    };

    _UUID();
    _UUID(int);
    
    String generate();

private:
    int mType;
};

}
#endif