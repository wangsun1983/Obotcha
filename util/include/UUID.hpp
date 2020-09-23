#ifndef __OBOTCHA_UUID_HPP__
#define __OBOTCHA_UUID_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "uuid.h"


namespace obotcha {

DECLARE_SIMPLE_CLASS(UUID) {

public:
    static const int Random;
    static const int Time;
    static const int TimeSafe;
    static const int Default;

    _UUID();
    _UUID(int);
    
    String generate();

private:
    int mType;
};

}
#endif